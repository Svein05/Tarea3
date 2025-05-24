# 👾 GraphQuest 

## 📌 Descripción:
Este programa ofrece al usuario la posibilidad de jugar **GraphQuest**, una aventura ambientada en un **laberinto compuesto por diversos escenarios interconectados**, donde deberá tomar decisiones y recolectar objetos útiles.

La partida comienza en el escenario "**Entrada principal**", y el objetivo es llegar al escenario final "**Salida**", eligiendo cuidadosamente cada ruta y seleccionando qué **ítems** recoger en el camino.

Cada movimiento que realiza el jugador consume **tiempo**, y el **peso acumulado de los objetos** en el inventario influye negativamente en su rendimiento. El desafío consiste en **obtener la mayor cantidad de puntos posibles** mediante la recolección de ítems, sin quedarse sin tiempo.

## ⚙️ Como compilar y ejecutar:
Este programa fue desarrollado integramente en el lenguaje de **Programacion C** y puede implementarse facilmente usando **Visual Studio Code** junto con una extensión para C/C++, como C/C++ Extension Pack de Microsoft. Por consecuente, para comenzar a trabajar con el sistema en tu equipo local hay que tener en cuenta lo siguiente:

> #### ✅ Requisitos Previos
> - Instalar [Visual Studio Code](https://code.visualstudio.com/)
> - Instalar la extension [C/C++ (Microsoft)](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)
> - Instalar algun compilador de C (como **gcc**). Si te encuentras en Windows, es recomedable instalar [MinGW](https://www.mingw-w64.org/).

### 🚀 Pasos para Compilar y Ejecutar:
1. Descarga y descomprime el archivo `.zip` en tu entorno de trabajo.
2. Abre el proyecto en **Visual Studio Code**
    - Inicia _Visual Studio Code_.
    - Selecciona `Archivo > Abrir carpeta...` y selecciona la carpeta donde descomprimiste el proyecto _(Paso 1)_
3. Compila y Ejecuta el codigo
    - Abre el archivo principal (Por ejemplo, `main.c`)
    - Abre la terminal integrada (`Terminal > Nueva Terminal`)
    - En la terminal *(De preferencia Git Bash)*, compila el programa con el siguiente comando:
        ```
        gcc tdas/*.c tarea3.c -Wno-unused-result -o tarea3
        ```
    - Una vez compilado, puedes ejecutar el programa en la misma terminal, con:
        ```
        ./tarea3
        ```

## 🧠 Funcionalidades:

### ✅ Funcionando Correctamente
- Cargar laberinto mediante un archivo **CSV**.
- Iniciar partida en modo **Solitario**.
- Iniciar partida en modo **Multijugador**.


> #### ⚠️ Problemas Conocidos
> 

## Ejemplo de Uso:
### Menú Principal:
```
+--------------------------------------+
|              GraphQuest              |
+--------------------------------------+
| 1) Cargar Laberinto                  |
| 2) Iniciar Partida: Solitario        |
| 3) Iniciar Partida: Multijugador     |
| 4) Salir del Juego                   |
+--------------------------------------+
```
### 👾 Procedicimiento de Ejemplo:
#### 📌 Comienza cargando el laberinto en el sistema.
Antes de comenzar a jugar **GraphQuest**, es fundamental seleccionar la **opción 1**, ya que este paso permite **cargar el laberinto en el sistema**. Sin ello, no será posible iniciar la partida ni acceder a las funcionalidades del juego.
``` 
+--------------------------------------+
|              GraphQuest              |
+--------------------------------------+
| 1) Cargar Laberinto                  |
| 2) Iniciar Partida: Solitario        |
| 3) Iniciar Partida: Multijugador     |
| 4) Salir del Juego                   |
+--------------------------------------+
Ingrese su opcion: 1
Laberinto cargado exitosamente.
presione una tecla para continuar...
```

> Una vez cargado el laberinto, ya se puede iniciar una partida en cualquiera de los dos modos disponibles. Si el usuario intenta seleccionar nuevamente la **opción 1** tras haber cargado el archivo CSV, el sistema informará que el laberinto ya ha sido cargado.


#### 🎮 Iniciar partida en **Solitario**.
Para comenzar una partida en **modo solitario**, el usuario debe seleccionar la **opción 2** desde el menú principal. Una vez iniciada la partida, se desplegará el primer escenario junto a la información relevante del jugador.
```
+--------------------------------------+
|              GraphQuest              |
+--------------------------------------+
| 1) Cargar Laberinto                  |
| 2) Iniciar Partida: Solitario        |
| 3) Iniciar Partida: Multijugador     |
| 4) Salir del Juego                   |
+--------------------------------------+
Ingrese su opcion: 2
========================================
         GraphQuest: Un Jugador
========================================

+------------------------------+
| ESCENARIO                    |
+------------------------------+
| Entrada principal            |
|                              |
| Una puerta rechinante abre   |
| paso a esta mansion olvidada |
| por los dioses y los         |
| conserjes. El aire huele a   |
| humedad y a misterios sin    |
| resolver.                    |
|                              |
| Acciones Posibles:           |
| - ABAJO                      |
|                              |
| Objetos Disponibles:         |
| - (Sin Items Disponibles)    |
+------------------------------+

+------------------------------+
| JUGADOR                      |
+------------------------------+
| (Inventario Vacio)           |
| Peso Total: 0                |
| Puntaje Acumulado: 0         |
| Tiempo Restante: 10          |
+------------------------------+

========================================
1) Recoger Item(s)
2) Descartar Item(s)
3) Avanzar
4) Reiniciar Partida
5) Volver al Menu Principal
========================================
Ingrese su opcion:
```
> Durante la partida, el jugador podrá avanzar por los escenarios, tomar decisiones estratégicas, recolectar objetos y administrar su inventario y tiempo disponible. Cada acción influirá en el puntaje final obtenido al completar el laberinto.
#### 🎤 Buscar música por **Artista**
Si se desea buscar música por su **Artista**, se debe seleccionar la **opción 3** y luego ingresar el nombre del artista que desea buscar.
```
+------------------------------------------------+
|                   SpotiFind                    |
+------------------------------------------------+
|  1) Cargar Canciones                           |
|  2) Buscar por Genero                          |
|  3) Buscar por Artista                         |
|  4) Buscar por Tempo                           |
|  5) Crear Lista de Reproduccion                |
|  6) Agregar Cancion a la Lista                 |
|  7) Mostrar Canciones de una Lista             |
|  8) Salir del Programa                         |
+------------------------------------------------+
Ingrese su opcion: 3
Ingrese al artista a buscar: Gen Hoshino
----------------------------------------
Canciones del artista: Gen Hoshino      
----------------------------------------
ID: 0
Titulo de la cancion: Comedy
Artista: Gen Hoshino
Genero: acoustic
Album: Comedy
Tempo: 87.92
----------------------------------------
...
Presione una tecla para continuar...
```
> El programa mostrará todas las canciones del artista seleccionado por el usuario (*sin distinguir entre **mayúsculas** y **minúsculas***), incluyendo información relevante como su **ID**, **título**, **artista**, **género**, **álbum** y **tempo**. Si el usuario ingresa un artista que **no** se encuentra en el dataset, el programa le informará que el artista no está disponible.
#### 🎶 Buscar música por **Tempo**
Si se desea buscar canciones por **Tempo**, se debe seleccionar la **opción 4** y luego elegir el ***rango de tempo*** con el que quiere buscar las canciones: la **opción 1** para canciones lentas, la **opción 2** para canciones moderadas y la **opción 3** para canciones rápidas.
```
+------------------------------------------------+
|                   SpotiFind                    |
+------------------------------------------------+
|  1) Cargar Canciones                           |
|  2) Buscar por Genero                          |
|  3) Buscar por Artista                         |
|  4) Buscar por Tempo                           |
|  5) Crear Lista de Reproduccion                |
|  6) Agregar Cancion a la Lista                 |
|  7) Mostrar Canciones de una Lista             |
|  8) Salir del Programa                         |
+------------------------------------------------+
Ingrese su opcion: 4
Seleccione el rango de tempo:
1) Lentas (< 80 BPM)
2) Moderadas (80-120 BPM)
3) Rapidas (> 120 BPM)
Ingrese su opcion: 1
----------------------------------------
Canciones con tempo entre 0.00 y 80.00
----------------------------------------
ID: 1
Titulo de la cancion: Ghost - Acoustic
Artista: Ben Woodward
Genero: acoustic
Album: Ghost (Acoustic)
Tempo: 77.49
----------------------------------------
ID: 2
Titulo de la cancion: To Begin Again
Artistas: Ingrid Michaelson, ZAYN
Genero: acoustic
Album: To Begin Again
Tempo: 76.33
----------------------------------------
...
Presione una tecla para continuar...
```
> El programa mostrará todas las canciones asociadas al **rango de tempo** elegido (*sin distinguir entre **mayúsculas** y **minúsculas***), incluyendo datos importantes como su **ID**, **título**, **artista(s)**, **género**, **álbum** y **tempo**. Si se selecciona una opción fuera del rango de tempo, el programa le notificará que la opción elegida no es válida.
#### 🎵 Crear una **Playlist**.
Si se desea crear una **Playlist**, deberá seleccionar la **opción 5** y luego ingresar el nombre de la lista de reproducción que desea crear. 
```
+------------------------------------------------+
|                   SpotiFind                    |
+------------------------------------------------+
|  1) Cargar Canciones                           |
|  2) Buscar por Genero                          |
|  3) Buscar por Artista                         |
|  4) Buscar por Tempo                           |
|  5) Crear Lista de Reproduccion                |
|  6) Agregar Cancion a la Lista                 |
|  7) Mostrar Canciones de una Lista             |
|  8) Salir del Programa                         |
+------------------------------------------------+
Ingrese su opcion: 5
Ingrese el nombre de la lista de reproduccion: some acoustic
Lista de reproduccion 'some acoustic' creada exitosamente.
Presione una tecla para continuar...
```
> El programa mostrará un mensaje indicando si la lista de reproducción fue creada correctamente. Si se intenta crear una nueva lista con el **mismo nombre**, se le informará que ya existe una playlist con ese nombre y será redirigido al menú principal.
#### 🎶 Agregar una canción a una **Playlist**
Si se desea **agregar** una canción a una **playlist**, deberá seleccionar la **opción 6**, ingresar el nombre de una **playlist ya creada** y luego proporcionar el **ID** de la canción que desea **agregar**. 
```
+------------------------------------------------+
|                   SpotiFind                    |
+------------------------------------------------+
|  1) Cargar Canciones                           |
|  2) Buscar por Genero                          |
|  3) Buscar por Artista                         |
|  4) Buscar por Tempo                           |
|  5) Crear Lista de Reproduccion                |
|  6) Agregar Cancion a la Lista                 |
|  7) Mostrar Canciones de una Lista             |
|  8) Salir del Programa                         |
+------------------------------------------------+
Ingrese su opcion: 6
Ingrese el nombre de la lista de reproduccion: some acoustic
Ingrese el ID de la cancion a agregar: 1
----------------------------------------
Cancion Agregada a la Lista de Reproduccion 'some acoustic' 
ID: 1
Titulo: Ghost - Acoustic
----------------------------------------
Presione una tecla para continuar...
```
> Si se ingresa el ID de una **playlist inexistente**, se le informará y será redirigido al menú principal. Si proporciona el **ID** de una **canción que ya se encuentra en la playlist**, el programa avisará y también lo llevará de vuelta al menú principal.
#### 🎶 Visualizar canciones de una **Playlist** 
Si se desea **visualizar** las canciones de una **playlist**, deberá seleccionar la **opción 7**, ingresar el nombre de una **playlist ya existente** y se mostrarán las canciones por pantalla.
```
+------------------------------------------------+
|                   SpotiFind                    |
+------------------------------------------------+
|  1) Cargar Canciones                           |
|  2) Buscar por Genero                          |
|  3) Buscar por Artista                         |
|  4) Buscar por Tempo                           |
|  5) Crear Lista de Reproduccion                |
|  6) Agregar Cancion a la Lista                 |
|  7) Mostrar Canciones de una Lista             |
|  8) Salir del Programa                         |
+------------------------------------------------+
Ingrese su opcion: 7
Ingrese el nombre de la lista de reproduccion: some acoustic
----------------------------------------
Canciones en la lista de reproduccion 'some acoustic':
----------------------------------------
ID: 1
Titulo de la cancion: Ghost - Acoustic
Artistas: Ben Woodward
Genero: acoustic
Album: Ghost (Acoustic)
Tempo: 77.49
----------------------------------------
...
Presione una tecla para continuar...
```
> El programa mostrará en pantalla la **playlist** con su contenido, mostrando datos como el **nombre de la playlist**, seguido de las canciones: **ID**, **título**, **artista**, **género**, **álbum** y **tempo** de cada canción. Si se ingresa el nombre de una **playlist inexistente**, el programa le informará y lo redirigirá al menú. Si ingresa una **playlist** ya creada pero sin contenido, se le informará que la playlist está vacía y también volverá al menú.

## Contribuciones

### Elias Manriquez
- **Desarrolló la funcion principal del programa:** Implementó la funcion para cargar canciones desde el archivo CSV, buscar por género, por artista y por tempo.

- **Creación de la estructura del menú:** Diseño e implementación del flujo principal de interacción con el usuario, permitiendo acceder a las funcionalidades de la aplicación.

- **Creacion de las principales funciones:** Diseño y creo las funciones principales que necesita el programa

- **Documentación básica:** Agregó comentarios esenciales en el código y algunos detalles del README.

> Auto-evaluación: 5/5 (Aporte Excelente)

### Maximiliano Rodriguez
- **Optimización de la carga de datos:** Mejoró la función de carga de canciones para que sea más eficiente al procesar archivos CSV grandes.

- **Manejo de errores:** Implementó validación de entrada de datos y manejo de errores para mejorar la robustez del programa.

- **Mejoras en la interfaz de usuario:** Rediseñó el flujo de opciones y añadió un sistema de retroalimentación más claro para el usuario.

- **Desarrollo del README:** Redactó el archivo `README.md` y lo finalizó, documentando de manera clara el funcionamiento, uso y aspectos técnicos del programa.

>Auto-evaluación: 5/5 (Aporte excelente)

