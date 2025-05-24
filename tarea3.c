#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tdas/map.h"     
#include "tdas/list.h"
#include "tdas/extra.h"

#define LINE_WIDTH 28

typedef struct
{
    char *nombre;
    int puntos;
    int peso;
    int id;
} Objeto;

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

typedef struct
{
    Escenario *escenario_actual;
    List* inventario;
    int peso_actual;
    int puntaje;
    int tiempo;
    int terminado;
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

void imprimir_con_formato(const char *texto) 
{
    int len = strlen(texto);
    int i = 0;

    while (i < len) 
    {
        int j = i + LINE_WIDTH;

        // Si el texto restante es menor al ancho, imprime y termina
        if (j >= len) 
        {
            printf("| %-*s |\n", LINE_WIDTH, texto + i);
            break;
        }

        // Busca el último espacio antes de pasar el límite
        int espacio = j;
        while (espacio > i && texto[espacio] != ' ')
            espacio--;

        // Si no hay espacio (una palabra muy larga), corta al límite
        if (espacio == i) espacio = j;

        // Imprime la línea
        char buffer[LINE_WIDTH + 1];
        strncpy(buffer, texto + i, espacio - i);
        buffer[espacio - i] = '\0';
        printf("| %-*s |\n", LINE_WIDTH, buffer);

        // Salta los espacios consecutivos
        i = espacio;
        while (isspace(texto[i])) i++;
    }
}

void mostrar_menu(int menu)
{
    if (menu == 1)
    {
        puts("+--------------------------------------+");
        puts("|              GraphQuest              |");
        puts("+--------------------------------------+");
        puts("| 1) Cargar Laberinto                  |");
        puts("| 2) Iniciar Partida: Solitario        |");
        puts("| 3) Iniciar Partida: Multijugador     |");
        puts("| 4) Salir del Juego                   |");
        puts("+--------------------------------------+");
    }
    else if (menu == 2)
    {
        puts("========================================");
        puts("1) Recoger Item(s)");
        puts("2) Descartar Item(s)");
        puts("3) Avanzar");
        puts("4) Reiniciar Partida");
        puts("5) Volver al Menu Principal");
        puts("========================================");
    }
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

        MapPair* par_dest;

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

void iniciar_jugadores(int cantidad, Jugador* player1, Jugador* player2)
{
    player1->inventario = list_create();
    player1->peso_actual = 0;
    player1->puntaje = 0;
    player1->tiempo = 10;
    player1->escenario_actual = NULL;
    player1->terminado = 0;

    if (cantidad == 2 && player2 != NULL)
    {
        player2->inventario = list_create();
        player2->peso_actual = 0;
        player2->puntaje = 0;
        player2->tiempo = 10;
        player2->escenario_actual = NULL;
        player2->terminado = 0;
    }
}

int mostrar_objetos(List* items, int tipo)
{
    if (tipo == 1)
    {
        int hay_inventario = 0;
        for (Objeto* item = list_first(items) ; item != NULL ; item = list_next(items))
        {
            printf("| - #%02d / %-20s |\n", item->id, item->nombre);
            printf("|   Peso: %-2d  /  Puntos: %-2d    |\n", item->peso, item->puntos);
            puts("|                              |");
            hay_inventario = 1;
        }

        return hay_inventario;
    }
    else if (tipo == 2)
    {
        for (Objeto* obj = list_first(items); obj != NULL; obj = list_next(items))
            printf("  #%02d - %s (Peso: %d, Puntos: %d)\n", obj->id, obj->nombre, obj->peso, obj->puntos);
    }
}

void mostrar_terminado(Jugador* player)
{
    puts("Inventario final:");
    mostrar_objetos(player->inventario, 2);
    printf("Puntaje final: %d\n", player->puntaje);
}

void mostrar_estado(Jugador* jugador)
{
    Escenario* escenario_actual = jugador->escenario_actual;

    puts("+------------------------------+");
    puts("| ESCENARIO                    |");
    puts("+------------------------------+");
    printf("| %-28s |\n", escenario_actual->nombre);
    puts("|                              |");
    imprimir_con_formato(escenario_actual->descripcion);
    puts("|                              |");
    puts("| Acciones Posibles:           |");

    const char* dirs[] = {"ARRIBA", "ABAJO", "IZQUIERDA", "DERECHA"};
    Escenario* conexiones[] = {
        escenario_actual->arriba,
        escenario_actual->abajo,
        escenario_actual->izquierda,
        escenario_actual->derecha
    };
    int hay_direccion = 0;
    for (int i = 0; i < 4; i++) 
    {
        if (conexiones[i]) 
        {
            printf("| - %-26s |\n", dirs[i]);
            hay_direccion = 1;
        }
    }
    if (!hay_direccion) puts("| - (Ninguna)                  |\n");

    puts("|                              |");
    puts("| Objetos Disponibles:         |");
    int hay_objetos = mostrar_objetos(escenario_actual->objetos, 1);
    if (hay_objetos == 0) puts("| - (Sin Items Disponibles)    |");
    puts("+------------------------------+");

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

void recoger_items(Jugador* jugador)
{
    Escenario* esc = jugador->escenario_actual;
    if (list_first(esc->objetos) == NULL) 
    {
        printf("No hay objetos para recoger en este escenario.\n");
        return;
    }

    puts("\nObjetos disponibles para recoger:");
    mostrar_objetos(esc->objetos, 2);

    printf("Ingrese el ID del objeto a recoger (0 para cancelar): ");
    int id_elegido;
    scanf("%d", &id_elegido);

    if (id_elegido == 0) {
        puts("Accion cancelada.");
        return;
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
            printf("Tiempo Restante: %d - 1 = %d", jugador->tiempo + 1, jugador->tiempo);

            if (jugador->tiempo <= 0)
            {
                puts("DERROTA - Se ha agotado el tiempo");
                jugador->terminado = 1;
            }

            return;
        }
    }

    puts("No existe un objeto con ese ID en este escenario.");
}

void descartar_items(Jugador* jugador)
{
    if (list_first(jugador->inventario) == NULL) 
    {
        printf("No tienes objetos en tu inventario para descartar.\n");
        return;
    }

    puts("\nObjetos en tu inventario:");
    mostrar_objetos(jugador->inventario, 2);

    printf("Ingrese el ID del objeto a descartar (0 para cancelar): ");
    int id_elegido;
    scanf("%d", &id_elegido);

    if (id_elegido == 0) {
        printf("Accion cancelada.\n");
        return;
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

            return;
        }
    }

    printf("No existe un objeto con ese ID en tu inventario.\n");
}

void avanzar(Jugador* jugador)
{
    Escenario* esc = jugador->escenario_actual;
    const char* dirs[] = {"ARRIBA", "ABAJO", "IZQUIERDA", "DERECHA"};
    Escenario* conexiones[] = {esc->arriba, esc->abajo, esc->izquierda, esc->derecha};

    // Mostrar opciones disponibles
    printf("\nOpciones para Avanzar\n");
    int opciones[4];
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (conexiones[i]) {
            printf(" %d) %s (%s)\n", count + 1, dirs[i], conexiones[i]->nombre);
            opciones[count] = i;
            count++;
        }
    }
    if (count == 0) {
        printf("No hay caminos disponibles desde aquí.\n");
        return;
    }

    printf("Elija una opcion (0 para cancelar): ");
    int eleccion;
    scanf("%d", &eleccion);

    if (eleccion <= 0 || eleccion > count) {
        printf("Movimiento cancelado.\n");
        return;
    }

    int dir_idx = opciones[eleccion - 1];
    Escenario* esc_inicial = jugador->escenario_actual;
    jugador->escenario_actual = conexiones[dir_idx];
    printf("Te has movido de %s hacia %s.\n", esc_inicial->nombre, jugador->escenario_actual->nombre);

    // Descontar tiempo: T = ((peso_actual + 1) / 10), mínimo 1
    int tiempo_usado = (jugador->peso_actual + 1) / 10;
    if (tiempo_usado < 1) tiempo_usado = 1;
    jugador->tiempo -= tiempo_usado;
    printf("Tiempo consumido en el movimiento: %d\n", tiempo_usado);
    printf("Tiempo restante: %d\n", jugador->tiempo);

    // Revisar si se acabó el tiempo
    int en_final = (jugador->escenario_actual->is_final && strcmp(jugador->escenario_actual->is_final, "Si") == 0);
    int sin_tiempo = (jugador->tiempo <= 0);

    if (en_final && sin_tiempo) {
        printf("\n¡Has llegado al escenario final justo cuando se agotó el tiempo!\n");
        printf("Inventario final:\n");
        for (Objeto* item = list_first(jugador->inventario); item != NULL; item = list_next(jugador->inventario))
            printf("  #%02d - %s (Puntos: %d)\n", item->id, item->nombre, item->puntos);
        printf("Puntaje final: %d\n", jugador->puntaje);
        jugador->terminado = 1;
        return;
    }
    if (sin_tiempo) {
        printf("\n¡Se ha agotado el tiempo! Has perdido.\n");
        printf("Inventario final:\n");
        for (Objeto* item = list_first(jugador->inventario); item != NULL; item = list_next(jugador->inventario))
            printf("  #%02d - %s (Puntos: %d)\n", item->id, item->nombre, item->puntos);
        printf("Puntaje final: %d\n", jugador->puntaje);
        jugador->terminado = 1;
        return;
    }
    if (en_final) {
        printf("\n¡Has llegado al escenario final!\n");
        printf("Inventario final:\n");
        for (Objeto* item = list_first(jugador->inventario); item != NULL; item = list_next(jugador->inventario))
            printf("  #%02d - %s (Puntos: %d)\n", item->id, item->nombre, item->puntos);
        printf("Puntaje final: %d\n", jugador->puntaje);
        jugador->terminado = 1;
        return;
    }
}

void reiniciar_partida(int jugadores, Jugador* player1, Jugador* player2, Map* escenarios)
{
    // Escenario inicial (primer escenario del mapa)
    Escenario* inicial = (Escenario*) map_first(escenarios)->value;

    // Reinicializa inventario, puntaje, peso y tiempo usando la función existente
    iniciar_jugadores(jugadores, player1, player2);

    // Asigna el escenario inicial a ambos jugadores
    player1->escenario_actual = inicial;
    if (jugadores == 2 && player2 != NULL)
        player2->escenario_actual = inicial;

    printf("La Partida se Reincio\n");
}

void empezar_juego(Map* escenarios, int jugadores)
{
    if (map_first(escenarios) == NULL) 
    {
        puts("No se ha cargado el Juego (Opcion 1)");
        return;
    }

    limpiarPantalla();

    Jugador* player1 = (Jugador*) malloc(sizeof(Jugador));
    Jugador* player2 = (jugadores == 2) ? (Jugador*) malloc(sizeof(Jugador)) : NULL;

    iniciar_jugadores(jugadores, player1, player2);

    player1->escenario_actual = (Escenario*) map_first(escenarios)->value;
    if (jugadores == 2) player2->escenario_actual = (Escenario*) map_first(escenarios)->value;

    int turno = 1;
    char opcion;
    
    while(1)
    {
        Jugador* actual = (turno == 1) ? player1 : player2;
        if (actual->terminado) 
        {
            printf("El Jugador %d ya terminó su partida.\n", turno);
            if (jugadores == 2 && player1->terminado) turno = 2;
            if (jugadores == 2 && player2->terminado) turno = 1;
            continue;
        }

        puts("========================================");
        if (jugadores == 1)
            puts("         GraphQuest: Un Jugador");
        else if (jugadores == 2)
            puts("         GraphQuest: Multijugador");
        puts("========================================\n");

        mostrar_estado(actual);
        if (jugadores == 2) printf(">>> TURNO DE JUGADOR %d <<<\n\n", turno);
        mostrar_menu(2);

        printf("Ingrese su opcion: ");
        scanf(" %c", &opcion);

        switch (opcion)
        {
            case '1':
                recoger_items(actual);
                break;
            case '2':
                descartar_items(actual);
                break;
            case '3':
                avanzar(actual);
                break;
            case '4':
                reiniciar_partida(jugadores, player1, player2, escenarios);
                break;
            case '5':
                return;
        }

        if (jugadores == 2 && ((player1->terminado && !player2->terminado)
            || (player2->terminado && !player1->terminado)))
        {
            mostrar_terminado(actual);
        }

        if (jugadores == 2 && !player1->terminado && !player2->terminado) turno = (turno == 1) ? 2 : 1;

        if (jugadores == 2 && player1->terminado && player2->terminado) {
            printf("\n=== ¡Ambos jugadores han terminado! ===\n");
            printf("Inventario Jugador 1:\n");
            for (Objeto* item = list_first(player1->inventario); item != NULL; item = list_next(player1->inventario))
                printf("  #%02d - %s (Puntos: %d)\n", item->id, item->nombre, item->puntos);
            printf("Puntaje Jugador 1: %d\n", player1->puntaje);

            printf("\nInventario Jugador 2:\n");
            for (Objeto* item = list_first(player2->inventario); item != NULL; item = list_next(player2->inventario))
                printf("  #%02d - %s (Puntos: %d)\n", item->id, item->nombre, item->puntos);
            printf("Puntaje Jugador 2: %d\n", player2->puntaje);

            printf("\nPuntaje Total: %d\n", player1->puntaje + player2->puntaje);
            break;
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();
    }
    
}

int main()
{
    char opcion;

    Map* mapa_escenarios = map_create(is_equal_int);
    limpiarPantalla();

    do 
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
                empezar_juego(mapa_escenarios, 1);
                break;
            case '3':
                empezar_juego(mapa_escenarios, 2);
                break;
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();

    } while (opcion != '4');

  return 0;
}
