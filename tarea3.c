#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tdas/map.h"       // Asumo que tienes este TDA
#include "tdas/list.h"
#include "tdas/extra.h"

#define LINE_WIDTH 28

typedef struct
{
    char *nombre;
    int puntos;
    int peso;
} Objeto;

typedef struct
{
    int id;
    char *nombre;
    char *descripcion;
    List* objetos;
    Map* conexiones;
    char* is_final;
} Escenario;

typedef struct
{
    Escenario *escenario_actual;
    List* inventario;
    int peso_actual;
    int puntaje;
    int tiempo;
} Jugador;

// Función de hash para claves de tipo string
unsigned int string_hash(void *key) 
{
    char *str = (char *)key;
    unsigned int hash = 0;

    while (*str) 
        hash += (unsigned char)(*str++);

    return hash;
}

// Función de hash para claves enteras
unsigned int int_hash(void *key) 
{
    unsigned int x = *(unsigned int *)key;
    return x * 31;  // Multiplicamos por un primo pequeño
}

/**
     Compara dos claves de tipo string para determinar si son iguales.
     Esta función se utiliza para inicializar mapas con claves de tipo string.

     @param key1 Primer puntero a la clave string.
     @param key2 Segundo puntero a la clave string.
     @return Retorna 1 si las claves son iguales, 0 de lo contrario.
*/
int is_equal_str(void *key1, void *key2)
{
    return strcmp((char *)key1, (char *)key2) == 0;
}

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
        puts("========================================");
        puts("             GraphQuest");
        puts("========================================");
        puts("1) Cargar Laberinto desde Archivo CSV");
        puts("2) Iniciar Partida: Solitario");
        puts("3) Iniciar Partida: Multijugador");
        puts("4) Salir");
    }
    else if (menu == 2)
    {
        puts("========================================");
        puts("1) Recoger Item(s)");
        puts("2) Descartar Item(s)");
        puts("3) Avanzar");
        puts("4) Reinicar Partida");
        puts("5) Salir");
    }
}

void conectar_escenarios(Map* mapa_escenarios, Map* conexiones_ids)
{
    const char* direcciones[] = {"ARRIBA", "ABAJO", "IZQUIERDA", "DERECHA"};

    MapPair* par = map_first(mapa_escenarios);
    while (par)
    {
        Escenario* esc = (Escenario*) par->value;

        MapPair* par_conex_temp = map_search(conexiones_ids, &(esc->id));
        Map* conexiones_temp = par_conex_temp ? (Map*) par_conex_temp->value : NULL;

        if (!conexiones_temp) {
            par = map_next(mapa_escenarios);
            continue;
        }

        // Si conexiones ya existía, solo limpiar el mapa para no perder memoria
        if (esc->conexiones)
            map_clean(esc->conexiones);
        else
            esc->conexiones = map_create(is_equal_str, string_hash);

        for (int i = 0; i < 4; i++)
        {
            const char* dir = direcciones[i];

            MapPair* par_id_conexion = map_search(conexiones_temp, (void*)dir);
            int* id_conexion = par_id_conexion ? (int*) par_id_conexion->value : NULL;
            if (!id_conexion || *id_conexion == -1) continue;

            MapPair* par_destino = map_search(mapa_escenarios, id_conexion);
            Escenario* destino = par_destino ? (Escenario*) par_destino->value : NULL;
            if (!destino) continue;

            map_insert(esc->conexiones, (void*)dir, destino);
        }

        par = map_next(mapa_escenarios);
    }
}

void cargar_lab(Map* escenarios)
{
    FILE *archivo = fopen("data/graphquest.csv", "r");
    if (archivo == NULL) 
    {
        perror("Error al abrir el archivo");
        return;
    }

    leer_linea_csv(archivo, ','); // Saltar encabezados

    Map* conexiones_ids = map_create(is_equal_int, int_hash);

    char **campos;
    while ((campos = leer_linea_csv(archivo, ',')) != NULL) 
    {
        Escenario* escenario = (Escenario*) malloc(sizeof(Escenario));
        escenario->id = atoi(campos[0]);
        escenario->nombre = strdup(campos[1]);
        escenario->descripcion = strdup(campos[2]);
        escenario->objetos = list_create();
        escenario->conexiones = NULL;
        escenario->is_final = strdup(campos[8]);

        // Cargar objetos
        List* items = split_string(campos[3], ";");
        for (char *item = list_first(items); item != NULL; item = list_next(items))
        {
            List* values = split_string(item, ",");
            if (list_size(values) < 3) continue;

            Objeto* obj = (Objeto*) malloc(sizeof(Objeto));

            char* val0 = NULL;
            char* val1 = NULL;
            char* val2 = NULL;

            val0 = list_first(values);
            val1 = list_next(values);
            val2 = list_next(values);

            obj->nombre = strdup(val0);
            obj->puntos = atoi(val1);
            obj->peso = atoi(val2);

            list_pushBack(escenario->objetos, obj);

            // Liberar valores
            for (char* val = list_first(values); val != NULL; val = list_next(values))
                free(val);

            list_clean(values);
            free(values);
        }
        list_clean(items);
        free(items);

        // Guardar conexiones como IDs
        Map* temp_conexiones = map_create(is_equal_str, string_hash);

        int *arriba = malloc(sizeof(int)); *arriba = atoi(campos[4]);
        int *abajo = malloc(sizeof(int)); *abajo = atoi(campos[5]);
        int *izq = malloc(sizeof(int)); *izq = atoi(campos[6]);
        int *der = malloc(sizeof(int)); *der = atoi(campos[7]);

        map_insert(temp_conexiones, "ARRIBA", arriba);
        map_insert(temp_conexiones, "ABAJO", abajo);
        map_insert(temp_conexiones, "IZQUIERDA", izq);
        map_insert(temp_conexiones, "DERECHA", der);

        int *id_clave = malloc(sizeof(int));
        *id_clave = escenario->id;

        map_insert(escenarios, id_clave, escenario);
        map_insert(conexiones_ids, id_clave, temp_conexiones);
    }

    fclose(archivo);

    conectar_escenarios(escenarios, conexiones_ids);

    // Liberar conexiones_ids y sus int* internos
    MapPair* par = map_first(conexiones_ids);
    while (par)
    {
        Map* temp = (Map*) par->value;
        const char* direcciones[] = {"ARRIBA", "ABAJO", "IZQUIERDA", "DERECHA"};
        for (int i = 0; i < 4; i++)
        {
            MapPair* par_id = map_search(temp, (void*)direcciones[i]);
            int* id = par_id ? (int*) par_id->value : NULL;
            if (id) free(id);
        }
        map_clean(temp);
        free(temp);   // Liberar el mapa temporal
        free(par->key); // liberar clave int*
        par = map_next(conexiones_ids);
    }
    map_clean(conexiones_ids);
    free(conexiones_ids);  // Liberar el mapa conexiones_ids


}

void iniciar_jugadores(int cantidad, Jugador* player1, Jugador* player2)
{
    player1->inventario = list_create();
    player1->peso_actual = 0;
    player1->puntaje = 0;
    player1->tiempo = 10;
    player1->escenario_actual = NULL;

    if (cantidad == 2 && player2 != NULL)
    {
        player2->inventario = list_create();
        player2->peso_actual = 0;
        player2->puntaje = 0;
        player2->tiempo = 10;
        player2->escenario_actual = NULL;
    }
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
    char* dirs[] = {"ARRIBA", "ABAJO", "IZQUIERDA", "DERECHA"};
    //char* flechas[] = {"[↑]", "[↓]", "[←]", "[→]"};
    int hay_direccion = 0;
    for (int i = 0; i < 4; i++) 
    {
        if (map_search(escenario_actual->conexiones, (void*)dirs[i])) 
        {
            printf("| - %-26s |\n", dirs[i]);
            hay_direccion = 1;
        }
    }
    if (!hay_direccion) puts("| - (Ninguna)                  |\n");

    puts("|                              |");
    puts("| Objetos Disponibles:         |");
    int hay_objetos = 0;
    for (Objeto* item = list_first(escenario_actual->objetos) ; item != NULL ; item = list_next(escenario_actual->objetos))
    {
        printf("| - %-26s |\n", item->nombre);
        printf("|   Peso: %-2d  -  Puntos: %-2d    |\n", item->peso, item->puntos);
        puts("|                              |");
        hay_objetos = 1;
    }
    if (!hay_objetos) puts("| - (Sin Items Disponibles)    |");
    puts("+------------------------------+");

    puts("\n+------------------------------+");
    puts("| JUGADOR                      |");
    puts("+------------------------------+");
    int peso_total = 0, puntaje_total = 0, hay_inventario = 0;
    for (Objeto* item = list_first(jugador->inventario) ; item != NULL ; item = list_next(jugador->inventario))
    {
        printf("| - %-26s |\n", item->nombre);
        printf("|   Peso: %-2d  -  Puntos: %-2d    |\n", item->peso, item->puntos);
        puts("|                              |");
        peso_total += item->peso;
        puntaje_total += item->puntos;
        hay_inventario = 1;
    }
    if (!hay_inventario) puts("| - (Inventario Vacio)         |");

    printf("| Peso Total: %-16d |\n", peso_total);
    printf("| Puntaje Acumulado: %-9d |\n", puntaje_total);
    printf("| Tiempo Restante: %-11d |\n", jugador->tiempo);
    puts("+------------------------------+");
    printf("\n");
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
    do
    {
        Jugador* actual = (turno == 1) ? player1 : player2;
        puts("========================================");
        if (jugadores == 1)
            puts("         GraphQuest: Un Jugador");
        else if (jugadores == 2)
            puts("         GraphQuest: Multijugador");
        puts("========================================\n");

        mostrar_estado(actual);
        mostrar_menu(2);

        printf("Ingrese su opción: ");
        scanf(" %c", &opcion);

        switch (opcion)
        {
            case '1':
                //recoger_items();
                break;
            case '2':
                //descartar_items();
                break;
            case '3':
                //avanzar();
                break;
            case '4':
                //reinicar_partida();
                break;
        }

        if (jugadores == 2) turno = (turno == 1) ? 2 : 1;

    } while (opcion != '5');
    
}

int main()
{
    char opcion;

    Map* mapa_escenarios = map_create(is_equal_int, int_hash);
    limpiarPantalla();

    do 
    {
        mostrar_menu(1);
    
        printf("Ingrese su opción: ");
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
