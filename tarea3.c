#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tdas/map.h"     
#include "tdas/list.h"
#include "tdas/extra.h"

#define LINE_WIDTH 28

// Se crea el struct Objeto
typedef struct
{
    char *nombre;
    int puntos;
    int peso;
    int id;
} Objeto;

// Se crea el struct Escenario
typedef struct Escenario Escenario;
struct Escenario
{
    int id;
    char *nombre;
    char *descripcion;
    List* objetos;
    Escenario* arriba;
    Escenario* abajo;
    Escenario* izquierda;
    Escenario* derecha;
    char* is_final;
};

// Se crea el struct Jugador
typedef struct
{
    Escenario *escenario_actual;
    List* inventario;
    int peso_actual;
    int puntaje;
    int tiempo;
    int terminado;
    int llego_al_final;
} Jugador;

/**
    Compara dos claves de tipo entero para determinar si son iguales.
    Esta función se utiliza para inicializar mapas con claves de tipo entero.

    @param key1 Primer puntero a la clave entera.
    @param key2 Segundo puntero a la clave entera.
    @return Retorna 1 si las claves son iguales, 0 de lo contrario.
*/
int is_equal_int(void *key1, void *key2)
{
    return *(int *)key1 == *(int *)key2; // Compara valores enteros directamente
}

// Funcion para poder imprimir de manera que este acorde con los limites
// y se vea uniforme con el programa
void imprimir_con_formato(const char *texto) 
{
    // Tomamo el largo de la cadena
    int len = strlen(texto);
    int i = 0;

    // Hacemos un bucle hasta que la variable alcance al largo de la cadena
    while (i < len) 
    {
        // Usamos LINE_WIDTH como el ancho que tendra el texto
        // Indicado por el cuadro y sus limites
        int j = i + LINE_WIDTH;

        // Si el texto restante es menor al ancho, imprime y termina
        if (j >= len) 
        {
            printf("| %-*s |\n", LINE_WIDTH, texto + i);
            break;
        }

        // Busca el ultimo espacio antes de pasar el limite
        int espacio = j;
        while (espacio > i && texto[espacio] != ' ') espacio--;

        // Si no hay espacio se corta al limite
        if (espacio == i) espacio = j;

        // Se imprime la linea
        char buffer[LINE_WIDTH + 1];
        strncpy(buffer, texto + i, espacio - i);
        buffer[espacio - i] = '\0';
        printf("| %-*s |\n", LINE_WIDTH, buffer);

        // Salta los espacios consecutivos
        i = espacio;
        while (isspace(texto[i])) i++;
    }
}

// Funcion para mostrar los diferentes menus,
// esto para la eficiencia del codigo
void mostrar_menu(int menu)
{
    // Menu principal
    if (menu == 1)
    {
        puts("+--------------------------------------+");
        puts("|              GraphQuest              |");
        puts("+--------------------------------------+");
        puts("| 1) Cargar Laberinto                  |");
        puts("| 2) Iniciar Partida: Solitario        |");
        puts("| 3) Iniciar Partida: Multijugador     |");
        puts("+--------------------------------------+");
    }
    // Menu para el Juego
    else if (menu == 2)
    {
        puts("========================================");
        puts("1) Recoger Item(s)");
        puts("2) Descartar Item(s)");
        puts("3) Avanzar");
        puts("4) Reiniciar Partida");
        puts("5) Salir del Juego");
        puts("========================================");
    }
}

// Funcion para mostrar los objetos de una lista,
// util para no repetir codigo
int mostrar_objetos(List* items, int tipo)
{
    // Menu tipo 1 para mostrar los items
    if (tipo == 1)
    {
        int hay_inventario = 0;
        for (Objeto* item = list_first(items) ; item != NULL ; item = list_next(items))
        {
            printf("| -> #%02d / %-19s |\n", item->id, item->nombre);
            printf("|    Peso: %-2d  ,  Puntos: %-2d   |\n", item->peso, item->puntos);
            puts("|                              |");
            hay_inventario = 1;
        }

        return hay_inventario;
    }
    // Menu tipo 2 para mostrar los items
    else if (tipo == 2)
    {
        for (Objeto* obj = list_first(items); obj != NULL; obj = list_next(items))
            printf("  #%02d - %s (Peso: %d, Puntos: %d)\n", obj->id, obj->nombre, obj->peso, obj->puntos);
    }
}

// Funcion para mostrar la informacion final del jugador
// al acabarse su tiempo o finalice el juego (solitario)
void mostrar_terminado(Jugador* player)
{
    puts("Inventario final:");
    mostrar_objetos(player->inventario, 2);
    printf("Puntaje final: %d\n", player->puntaje);
}

// Funcion para mostrar el estado de el jugador 
// o jugadores, dependiendo el tipo de juego.
void mostrar_estado(Jugador* jugador)
{
    // Tomamos el escenario actual del jugador
    Escenario* escenario_actual = jugador->escenario_actual;

    // Atravez de un formato especifico del programa
    // Imprimos el escenario, usando la funcion de
    // imprimir_con_formato() para la descripcion
    puts("+------------------------------+");
    puts("| ESCENARIO                    |");
    puts("+------------------------------+");
    printf("| %-28s |\n", escenario_actual->nombre);
    puts("|                              |");
    imprimir_con_formato(escenario_actual->descripcion);
    puts("|                              |");
    puts("| Acciones Posibles:           |");

    // Creamos un arrelgo para las direcciones.
    char* dirs[] = {"ARRIBA", "ABAJO", "IZQUIERDA", "DERECHA"};
    Escenario* conexiones[] = {
        escenario_actual->arriba,
        escenario_actual->abajo,
        escenario_actual->izquierda,
        escenario_actual->derecha
    };

    // Contador para saber si hay o no direcciones disponibles
    int hay_direccion = 0;
    for (int i = 0; i < 4; i++) 
    {
        if (conexiones[i]) 
        {
            printf("| - %-26s |\n", dirs[i]);
            hay_direccion = 1;
        }
    }
    // Verificamos que las haya
    if (!hay_direccion) puts("| - (Ninguna)                  |\n");

    // e imprimimos la informacion completa del escenario
    puts("|                              |");
    puts("| Objetos Disponibles:         |");
    int hay_objetos = mostrar_objetos(escenario_actual->objetos, 1);
    if (hay_objetos == 0) puts("| - (Sin Items Disponibles)    |");
    puts("+------------------------------+");

    // Ahora se imprime la informaciond del jugador
    // Con sus objetos, su peso total, su puntaje acumulado y su tiempo restante
    puts("\n+------------------------------+");
    puts("| JUGADOR                      |");
    puts("+------------------------------+");
    int hay_inventario = mostrar_objetos(jugador->inventario, 1);
    if (!hay_inventario) puts("| (Inventario Vacio)           |");
    printf("| Peso Total: %-16d |\n", jugador->peso_actual);
    printf("| Puntaje Acumulado: %-9d |\n", jugador->puntaje);
    printf("| Tiempo Restante: %-11d |\n", jugador->tiempo);
    puts("+------------------------------+");
    printf("\n");
}

// Funcion para mostrar el menu FINAL cuando se juega de manera
// multijugador, obteniendo un resumen completo de ambos jugadores
void mostrar_multijugador_terminado(Jugador* player1, Jugador* player2)
{
    // Obtenemos sus puntajes y si es que llegaron al final o no.
    int puntaje1 = player1->puntaje;
    int puntaje2 = player2->puntaje;
    int llego1 = player1->llego_al_final;
    int llego2 = player2->llego_al_final;

    // Titulo principal
    puts("+------------------------------+");
    puts("|    EL JUEGO HA FINALIZADO    |");
    puts("+------------------------------+");

    // Informacion del Jugador 1
    puts("\n+------------------------------+");
    puts("| JUGADOR 1                    |");
    puts("+------------------------------+");
    int hay_inventario1 = mostrar_objetos(player1->inventario, 1);
    if (!hay_inventario1) puts("| (Inventario Vacio)           |");
    printf("| Puntaje Acumulado: %-9d |\n", puntaje1);
    printf("| Llego al Final? %s\n", (llego1 == 1) ? "SI" : "NO");
    puts("+------------------------------+\n");

    // Informacion del Jugador 2
    puts("+------------------------------+");
    puts("| JUGADOR 2                    |");
    puts("+------------------------------+");
    int hay_inventario2 = mostrar_objetos(player2->inventario, 1);
    if (!hay_inventario2) puts("| (Inventario Vacio)           |");
    printf("| Puntaje Acumulado: %-9d |\n", puntaje2);
    printf("| Llego al Final? %s\n", (llego2 == 1) ? "SI" : "NO");
    puts("+------------------------------+\n");

    // Aqui atravez de diferentes condiciones, podemos
    // identificar el ganador de el juego o si hubo empate.
    puts("+------------------------------+");
    if (llego1 && !llego2)
        printf("|    EL JUGADOR 1 HA GANADO    |\n");
    else if (!llego1 && llego2)
        printf("|    EL JUGADOR 2 HA GANADO    |\n");
    else if (!llego1 && !llego2)
        printf("|  NADIE GANO (NINGUNO LLEGO)  |\n");
    else if (puntaje1 > puntaje2)
        printf("|    EL JUGADOR 1 HA GANADO    |\n");
    else if (puntaje2 > puntaje1)
        printf("|    EL JUGADOR 2 HA GANADO    |\n");
    else
        printf("|       EMPATE EN PUNTOS       |\n");
    puts("+------------------------------+");
}

// Funcion para inicializar a los jugadores
void iniciar_jugadores(int cantidad, Jugador* player1, Jugador* player2)
{
    // Siempre se inicializara al Jugador 1
    player1->inventario = list_create();
    player1->peso_actual = 0;
    player1->puntaje = 0;
    player1->tiempo = 15;
    player1->escenario_actual = NULL;
    player1->terminado = 0;
    player1->llego_al_final = 0;

    // Si y solo si, hay un jugador 2, este se inicializara
    if (cantidad == 2 && player2 != NULL)
    {
        player2->inventario = list_create();
        player2->peso_actual = 0;
        player2->puntaje = 0;
        player2->tiempo = 15;
        player2->escenario_actual = NULL;
        player2->terminado = 0;
        player2->llego_al_final = 0;
    }
}

// Funcion para liberar la memoria de los inventarios de los jugadores
void liberar_inventario(List* inventario) 
{
    if (!inventario) return;
    list_clean(inventario);
    free(inventario);
}

// Funcion para liberar la memoria de los jugadoes
void liberar_jugador(Jugador* jugador) 
{
    if (!jugador) return;
    liberar_inventario(jugador->inventario);
    free(jugador);
}

// Funcion para liberar la memoria de los objetos
// del escenario
void liberar_objetos(List* lista) 
{
    if (!lista) return;
    Objeto* obj = list_first(lista);

    while (obj) 
    {
        free(obj->nombre);
        free(obj);
        obj = list_next(lista);
    }
    
    list_clean(lista);
    free(lista);
}

// Funcion para liberar la memoria de los escenarios, por completo
void liberar_escenarios(Map* escenarios) 
{
    if (!escenarios) return;
    MapPair* par = map_first(escenarios);

    while (par) 
    {
        Escenario* esc = (Escenario*)par->value;
        free(esc->nombre);
        free(esc->descripcion);
        free(esc->is_final);
        liberar_objetos(esc->objetos);
        free(esc);
        par = map_next(escenarios);
    }

    map_clean(escenarios);
    free(escenarios);
}

Map* map_copia_superficial(Map* original, int (*is_equal)(void*, void*)) {
    Map* copia = map_create(is_equal);
    for (MapPair* par = map_first(original); par != NULL; par = map_next(original)) {
        // Solo copia los punteros, no duplica la memoria de los datos
        map_insert(copia, par->key, par->value);
    }
    return copia;
}

void conectar_escenario(Map* escenarios, Escenario* esc, int* id, Escenario** direccion)
{
    if (id && *id != -1) {
        MapPair* par_dest = map_search(escenarios, id);
        *direccion = par_dest ? (Escenario*)par_dest->value : NULL;
    }
}

void cargar_lab(Map* escenarios)
{
    if (map_first(escenarios) != NULL)
    {
        puts("Ya ha sido cargado el CSV");
        return;
    }

    FILE *archivo = fopen("data/graphquest.csv", "r");
    if (archivo == NULL) 
    {
        perror("Error al abrir el archivo");
        return;
    }

    leer_linea_csv(archivo, ',');

    Map* conexiones_ids = map_create(is_equal_int);
    int id_objeto = 1; // Contador global de IDs de objetos

    char **campos;
    while ((campos = leer_linea_csv(archivo, ',')) != NULL) 
    {
        Escenario* escenario = (Escenario*) malloc(sizeof(Escenario));
        escenario->id = atoi(campos[0]);
        escenario->nombre = strdup(campos[1]);
        escenario->descripcion = strdup(campos[2]);
        escenario->objetos = list_create();
        escenario->arriba = NULL;
        escenario->abajo = NULL;
        escenario->izquierda = NULL;
        escenario->derecha = NULL;
        escenario->is_final = strdup(campos[8]);

        // Cargar objetos
        List* items = split_string(campos[3], ";");
        for (char *item = list_first(items); item != NULL; item = list_next(items))
        {
            List* values = split_string(item, ",");
            if (list_size(values) < 3) continue;

            Objeto* obj = (Objeto*) malloc(sizeof(Objeto));

            char* val0 = list_first(values);
            char* val1 = list_next(values);
            char* val2 = list_next(values);

            obj->nombre = strdup(val0);
            obj->puntos = atoi(val1);
            obj->peso = atoi(val2);
            obj->id = id_objeto++;

            list_pushBack(escenario->objetos, obj);

            list_clean(values);
            free(values);
        }
        list_clean(items);
        free(items);

        // Guardar conexiones como IDs (en orden: arriba, abajo, izq, der)
        List* ids = list_create();
        int *arriba = (int*)malloc(sizeof(int)); *arriba = atoi(campos[4]);
        int *abajo = (int*)malloc(sizeof(int)); *abajo = atoi(campos[5]);
        int *izq = (int*)malloc(sizeof(int)); *izq = atoi(campos[6]);
        int *der = (int*)malloc(sizeof(int)); *der = atoi(campos[7]);

        list_pushBack(ids, arriba);
        list_pushBack(ids, abajo);
        list_pushBack(ids, izq);
        list_pushBack(ids, der);

        int *id_clave = (int*)malloc(sizeof(int));
        *id_clave = escenario->id;

        map_insert(escenarios, id_clave, escenario);
        map_insert(conexiones_ids, id_clave, ids);
    }

    fclose(archivo);

    // Crear copia superficial de conexiones_ids
    Map* conexiones_ids_copia = map_copia_superficial(conexiones_ids, is_equal_int);

    MapPair* par_con = map_first(conexiones_ids_copia);
    while (par_con) 
    {
        int* id_clave = par_con->key;
        List* ids = (List*)par_con->value;

        // Busca el escenario original
        MapPair* par_esc = map_search(escenarios, id_clave);
        if (!par_esc) 
        {
            par_con = map_next(conexiones_ids_copia);
            continue;
        }

        Escenario* esc = (Escenario*)par_esc->value;

        int* id_arriba = list_first(ids);
        int* id_abajo = list_next(ids);
        int* id_izquierda = list_next(ids);
        int* id_derecha = list_next(ids);

        conectar_escenario(escenarios, esc, id_arriba, &esc->arriba);
        conectar_escenario(escenarios, esc, id_abajo, &esc->abajo);
        conectar_escenario(escenarios, esc, id_izquierda, &esc->izquierda);
        conectar_escenario(escenarios, esc, id_derecha, &esc->derecha);

        par_con = map_next(conexiones_ids_copia);
    }

    map_clean(conexiones_ids_copia);
    free(conexiones_ids_copia);
    map_clean(conexiones_ids);
    free(conexiones_ids);

    puts("Laberinto cargado exitosamente.");
}

int recoger_items(Jugador* jugador)
{
    Escenario* esc = jugador->escenario_actual;
    if (list_first(esc->objetos) == NULL) 
    {
        printf("No hay objetos para recoger en este escenario.\n");
        return 0;
    }

    puts("\nObjetos disponibles para recoger:");
    mostrar_objetos(esc->objetos, 2);

    printf("\nIngrese el ID del objeto a recoger (0 para cancelar): ");
    int id_elegido;
    if (scanf("%d", &id_elegido) != 1)
    {
        puts("Error: Entrada no valida.");
        return 0;
    }

    if (id_elegido == 0) {
        puts("Accion cancelada.");
        return 0;
    }

    // Buscar el objeto por ID
    for (Objeto* obj = list_first(esc->objetos); obj != NULL; obj = list_next(esc->objetos)) 
    {
        if (obj->id == id_elegido) 
        {
            list_pushBack(jugador->inventario, obj);
            jugador->peso_actual += obj->peso;
            jugador->puntaje += obj->puntos;
            jugador->tiempo -= 1;
            list_popCurrent(esc->objetos);
            printf("Has recogido: %s\n", obj->nombre);
            printf("Tiempo Restante: %d - 1 = %d\n", jugador->tiempo + 1, jugador->tiempo);

            if (jugador->tiempo <= 0)
            {
                puts("\nDERROTA - Se ha agotado el tiempo");
                jugador->terminado = 1;
            }

            return 1;
        }
    }

    puts("No existe un objeto con ese ID en este escenario.");
    return 0;
}

int descartar_items(Jugador* jugador)
{
    if (list_first(jugador->inventario) == NULL) 
    {
        printf("No tienes objetos en tu inventario para descartar.\n");
        return 0;
    }

    puts("\nObjetos en tu inventario:");
    mostrar_objetos(jugador->inventario, 2);

    printf("\nIngrese el ID del objeto a descartar (0 para cancelar): ");
    int id_elegido;
    if (scanf("%d", &id_elegido) != 1)
    {
        puts("Error: Entrada no valida.");
        return 0;
    }

    if (id_elegido == 0) {
        printf("Accion cancelada.\n");
        return 0;
    }

    // Buscar el objeto por ID
    for (Objeto* obj = list_first(jugador->inventario); obj != NULL; obj = list_next(jugador->inventario)) 
    {
        if (obj->id == id_elegido) 
        {
            jugador->peso_actual -= obj->peso;
            jugador->puntaje -= obj->puntos;
            list_popCurrent(jugador->inventario); // Elimina el objeto del inventario
            printf("Has descartado: %s.\n", obj->nombre);
            jugador->tiempo -= 1;
            printf("Tiempo Restante: %d - 1 = %d\n", jugador->tiempo + 1, jugador->tiempo);

            if (jugador->tiempo <= 0)
            {
                puts("DERROTA - Se ha agotado el tiempo");
                jugador->terminado = 1;
            }

            return 1;
        }
    }

    printf("No existe un objeto con ese ID en tu inventario.\n");
    return 0;
}

int avanzar(Jugador* jugador)
{
    Escenario* esc = jugador->escenario_actual;
    const char* dirs[] = {"ARRIBA", "ABAJO", "IZQUIERDA", "DERECHA"};
    Escenario* conexiones[] = {esc->arriba, esc->abajo, esc->izquierda, esc->derecha};

    // Mostrar opciones disponibles
    printf("\nOpciones para Avanzar\n");
    int opciones[4];
    int count = 0;
    for (int i = 0; i < 4; i++) 
    {
        if (conexiones[i]) 
        {
            printf(" %d) %s (%s)\n", count + 1, dirs[i], conexiones[i]->nombre);
            opciones[count] = i;
            count++;
        }
    }

    if (count == 0) 
    {
        printf("No hay caminos disponibles desde aquí.\n");
        return 0;
    }

    printf("\nElija una opcion (0 para cancelar): ");
    int eleccion;
    if (scanf("%d", &eleccion) != 1)
    {
        puts("Error: Entrada no valida.");
        return 0;
    }

    if (eleccion == 0) 
    {
        puts("Movimiento cancelado.");
        return 0;
    }
    else if (eleccion < 0 || eleccion > count)
    {
        puts("Movimiento no existente");
        return 0;
    }

    int dir_idx = opciones[eleccion - 1];
    Escenario* esc_inicial = jugador->escenario_actual;
    jugador->escenario_actual = conexiones[dir_idx];
    printf("\nTe has movido de %s hacia %s.\n", esc_inicial->nombre, jugador->escenario_actual->nombre);

    // Descontar tiempo: T = ((peso_actual + 1) / 10), mínimo 1
    int tiempo_usado = (jugador->peso_actual + 1) / 10;
    if (tiempo_usado < 1) tiempo_usado = 1;
    jugador->tiempo -= tiempo_usado;
    printf("Tiempo Restante: %d - %d = %d\n", jugador->tiempo + tiempo_usado, tiempo_usado, jugador->tiempo);

    // Revisar si se acabó el tiempo
    int en_final = (jugador->escenario_actual->is_final && strcmp(jugador->escenario_actual->is_final, "Si") == 0);
    int sin_tiempo = (jugador->tiempo <= 0);

    if (en_final) 
    {
        puts("\nFIN - Has llegado a la Salida");
        jugador->terminado = 1;
        jugador->llego_al_final = 1;
        return 1;
    }
    else if (sin_tiempo) 
    {
        puts("\nDERROTA - Se ha agotado el tiempo");
        jugador->terminado = 1;
        return 1;
    }

    return 1;
}

void reiniciar_partida(int jugadores, Jugador* player1, Jugador* player2, Map** escenarios)
{
    // Limpiar inventarios de los jugadores
    liberar_inventario(player1->inventario);
    if (jugadores == 2 && player2 != NULL)
        liberar_inventario(player2->inventario);

    // Limpiar escenarios y recargar el laberinto desde cero
    liberar_escenarios(*escenarios);
    *escenarios = map_create(is_equal_int);
    cargar_lab(*escenarios);

    // Reinicializa inventario, puntaje, peso y tiempo usando la función existente
    iniciar_jugadores(jugadores, player1, player2);

    // Asigna el escenario inicial a ambos jugadores
    player1->escenario_actual = (Escenario*) map_first(*escenarios)->value;
    if (jugadores == 2 && player2 != NULL)
        player2->escenario_actual = (Escenario*) map_first(*escenarios)->value;

    printf("La Partida se Reincio.\n");
}

void empezar_juego(Map** escenarios, int jugadores)
{
    if (map_first(*escenarios) == NULL) 
    {
        puts("No se ha cargado el Juego (Opcion 1)");
        return;
    }

    limpiarPantalla();

    Jugador* player1 = (Jugador*) malloc(sizeof(Jugador));
    Jugador* player2 = (jugadores == 2) ? (Jugador*) malloc(sizeof(Jugador)) : NULL;

    iniciar_jugadores(jugadores, player1, player2);

    player1->escenario_actual = (Escenario*) map_first(*escenarios)->value;
    if (jugadores == 2) player2->escenario_actual = (Escenario*) map_first(*escenarios)->value;

    int turno = 1;
    char opcion;
    
    while(1)
    {
        Jugador* actual = (turno == 1) ? player1 : player2;

        puts("========================================");
        if (jugadores == 1)
            puts("         GraphQuest: Un Jugador");
        else if (jugadores == 2)
            puts("         GraphQuest: Multijugador");
        puts("========================================\n");

        mostrar_estado(actual);

        if (jugadores == 2) printf(">>> TURNO DE JUGADOR %d <<<\n\n", turno);

        if (actual->terminado) 
        {
            if (jugadores == 2 && player1->terminado) turno = 2;
            if (jugadores == 2 && player2->terminado) turno = 1;
            continue;
        }

        mostrar_menu(2);

        printf("Ingrese su opcion: ");
        scanf(" %c", &opcion);

        int accion_consumida = 0;
        int estaba_terminado = actual->terminado;

        switch (opcion)
        {
            case '1':
                accion_consumida = recoger_items(actual);
                break;
            case '2':
                accion_consumida = descartar_items(actual);
                break;
            case '3':
                accion_consumida = avanzar(actual);
                break;
            case '4':
                reiniciar_partida(jugadores, player1, player2, escenarios);
                break;
            case '5':
                liberar_jugador(player1);
                if (jugadores == 2) liberar_jugador(player2);
                liberar_escenarios(*escenarios);
                exit(0);
                return;
        }

        if (jugadores == 1 && actual->terminado) 
        {
            mostrar_terminado(actual);
            liberar_jugador(player1);
            liberar_escenarios(*escenarios);
            *escenarios = map_create(is_equal_int);
            printf("Se reiniciara el Laberinto...\n");
            cargar_lab(*escenarios);
            break;
        }

        if (jugadores == 2)
        {
            if (!estaba_terminado && actual->terminado && !(player1->terminado && player2->terminado))
            {
                mostrar_terminado(actual);
            }

            if (accion_consumida && !player1->terminado && !player2->terminado)
            {
                turno = (turno == 1) ? 2 : 1;
            }

            if (player1->terminado && player2->terminado)
            {
                limpiarPantalla();
                mostrar_multijugador_terminado(player1, player2);
                liberar_jugador(player1);
                liberar_jugador(player2);
                liberar_escenarios(*escenarios);
                *escenarios = map_create(is_equal_int);
                printf("Se reiniciara el Laberinto...\n");
                cargar_lab(*escenarios);
                break;
            }
        }

        presioneTeclaParaContinuar();
        limpiarPantalla();
    }
}

int main()
{
    char opcion;
    limpiarPantalla();

    Map* mapa_escenarios = map_create(is_equal_int);

    while(1)
    {
        mostrar_menu(1);
    
        printf("Ingrese su opcion: ");
        scanf(" %c", &opcion);
    
        switch (opcion) 
        {
            case '1':
                cargar_lab(mapa_escenarios);
                break;
            case '2':
                empezar_juego(&mapa_escenarios, 1);
                break;
            case '3':
                empezar_juego(&mapa_escenarios, 2);
                break;
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();

    }

    liberar_escenarios(mapa_escenarios);

  return 0;
}
