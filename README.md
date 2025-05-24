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
- **Recoleccion** de ítems.
- **Descartar** Ítems.
- **Avanzar** al siguiente escenario.
- **Reiniciar** Partida.
- **Salir** del juego.

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
+--------------------------------------+
Ingrese su opcion: 2
```
```
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
5) Salir del Juego
========================================
Ingrese su opcion: _
```
> Durante la partida, el jugador podrá avanzar por los escenarios, tomar decisiones estratégicas, recolectar objetos y administrar su inventario y tiempo disponible. Cada acción influirá en el puntaje final obtenido al completar el laberinto. 
#### 🧭 Recoleccion de  **Ítems**.
Para recoger ítems, el jugador debe seleccionar la **opción 1** desde el menú de juego. El sistema mostrará los objetos disponibles en el escenario actual, incluyendo su **ID**, **peso** y **puntos**. Luego, solicitará al usuario que ingrese el **ID del ítem que desea recoger**. 
```
========================================
         GraphQuest: Un Jugador
========================================

+------------------------------+        
| ESCENARIO                    |        
+------------------------------+        
| Cocina                       |        
|                              |        
| Restos de una batalla        |        
| culinaria. Cuchillos por     |        
| aqui, migajas por alla.      |        
| Alguien cocinoÔÇª o fue      |        
| cocinado.                    |        
|                              |        
| Acciones Posibles:           |        
| - ARRIBA                     |        
| - ABAJO                      |        
| - DERECHA                    |        
|                              |
| Objetos Disponibles:         |
| - #03 / Cuchillo             |
|   Peso: 1   /  Puntos: 3     |
|                              |
| - #04 / Pan                  |
|   Peso: 1   /  Puntos: 2     |
|                              |
+------------------------------+

+------------------------------+
| JUGADOR                      |
+------------------------------+
| (Inventario Vacio)           |
| Peso Total: 0                |
| Puntaje Acumulado: 0         |
| Tiempo Restante: 9           |
+------------------------------+

========================================
1) Recoger Item(s)
2) Descartar Item(s)
3) Avanzar
4) Reiniciar Partida
5) Salir del Juego
========================================
Ingrese su opcion: 1

Objetos disponibles para recoger:
  #03 - Cuchillo (Peso: 1, Puntos: 3)
  #04 - Pan (Peso: 1, Puntos: 2)

Ingrese el ID del objeto a recoger (0 para cancelar): 03
Has recogido: Cuchillo
Tiempo Restante: 9 - 1 = 8
Presione una tecla para continuar...
```
> Al seleccionar un ítem, el programa verifica que el ID ingresado corresponda a uno válido en el escenario. No es necesario preocuparse por ceros a la izquierda: ingresar (03) o (3) funcionará de igual manera si ese ítem está disponible. Una vez confirmado, el objeto se añade al inventario del jugador, su peso y puntaje se suman, y se descuenta una unidad de tiempo restante como penalización por la acción. Luego, el jugador puede continuar explorando el laberinto.

#### ❌ Descartar Ítems.
Para descartar ítems, el jugador deberá seleccionar la opcion 2 desde el menú del juego. El sistema mostrará todos los objetos actualmente almacenados en el inventario del jugador, junto a su **ID**, **nombre**, **peso** y **puntos**. Luego, se solicitará el ID del objeto que se desea eliminar.
```
========================================
         GraphQuest: Un Jugador
========================================

+------------------------------+        
| ESCENARIO                    |        
+------------------------------+        
| Cocina                       |        
|                              |        
| Restos de una batalla        |        
| culinaria. Cuchillos por     |        
| aqui, migajas por alla.      |        
| Alguien cocinoÔÇª o fue      |        
| cocinado.                    |        
|                              |        
| Acciones Posibles:           |        
| - ARRIBA                     |        
| - ABAJO                      |        
| - DERECHA                    |        
|                              |
| Objetos Disponibles:         |
| - #04 / Pan                  |
|   Peso: 1   /  Puntos: 2     |
|                              |
+------------------------------+

+------------------------------+
| JUGADOR                      |
+------------------------------+
| (Inventario Vacio)           |
| Peso Total: 0                |
| Puntaje Acumulado: 0         |
| Tiempo Restante: 9           |
+------------------------------+

========================================
1) Recoger Item(s)
2) Descartar Item(s)
3) Avanzar
4) Reiniciar Partida
5) Salir del Juego
========================================
Ingrese su opcion: 2

Objetos en tu inventario:
  #03 - Cuchillo (Peso: 1, Puntos: 3)

Ingrese el ID del objeto a descartar (0 para cancelar): 03
Has descartado: Cuchillo.
Tiempo Restante: 8 - 1 = 7
Presione una tecla para continuar...
```
> Al seleccionar un ítem para descartar, el programa verifica que el ID ingresado exista en el inventario del jugador. No importa si se ingresa el ID con ceros a la izquierda (03) o sin ellos (3), ya que ambos serán interpretados correctamente si el objeto está disponible. Una vez confirmado, el objeto es eliminado del inventario, su peso y puntos se descuentan, y se penaliza al jugador restando una unidad de tiempo restante. Luego de esta acción, el jugador puede seguir su aventura por el laberinto.

#### 🏃‍♂️ Avanzar al siguiente escenario.
Para avanzar, el jugador debe seleccionar la **opción 3** desde el menú de juego. Al hacerlo, el sistema mostrará por pantalla las direcciones disponibles y los escenarios a los que conducen. El jugador deberá elegir la dirección deseada ingresando el número correspondiente.
```
========================================
         GraphQuest: Un Jugador
========================================

+------------------------------+        
| ESCENARIO                    |        
+------------------------------+        
| Cocina                       |        
|                              |        
| Restos de una batalla        |        
| culinaria. Cuchillos por     |        
| aqui, migajas por alla.      |        
| Alguien cocinoÔÇª o fue      |        
| cocinado.                    |        
|                              |        
| Acciones Posibles:           |        
| - ARRIBA                     |        
| - ABAJO                      |        
| - DERECHA                    |        
|                              |
| Objetos Disponibles:         |
| - #04 / Pan                  |
|   Peso: 1   /  Puntos: 2     |
|                              |
+------------------------------+

+------------------------------+
| JUGADOR                      |
+------------------------------+
| (Inventario Vacio)           |
| Peso Total: 0                |
| Puntaje Acumulado: 0         |
| Tiempo Restante: 9           |
+------------------------------+

========================================
1) Recoger Item(s)
2) Descartar Item(s)
3) Avanzar
4) Reiniciar Partida
5) Salir del Juego
========================================
Ingrese su opcion: 3

Opciones para Avanzar
 1) ARRIBA (Entrada principal)
 2) ABAJO (Jardin)
 3) DERECHA (Comedor)

Elija una opcion (0 para cancelar): 2
Te has movido de Cocina hacia Jardin.
Tiempo consumido en el movimiento: 1
Tiempo restante: 6
Presione una tecla para continuar...
```
> Al elegir la dirección, el programa confirma hacia qué escenario se ha movido el jugador. Luego calcula el tiempo perdido usando la fórmula: Tiempo perdido = ((peso total del inventario + 1) / 10). Esto refleja el esfuerzo adicional que implica moverse con peso. El valor resultante se resta al tiempo restante del jugador. Finalmente, se actualiza la pantalla con la nueva ubicación y el tiempo disponible para continuar explorando el laberinto.

#### 🔁 Reiniciar Partida
Para reinciar partida, el jugador debe seleccionar la **opcion 4** en el menú del juego.
```
========================================
         GraphQuest: Un Jugador
========================================

+------------------------------+        
| ESCENARIO                    |        
+------------------------------+        
| Cocina                       |        
|                              |        
| Restos de una batalla        |        
| culinaria. Cuchillos por     |        
| aqui, migajas por alla.      |        
| Alguien cocinoÔÇª o fue      |        
| cocinado.                    |        
|                              |        
| Acciones Posibles:           |        
| - ARRIBA                     |        
| - ABAJO                      |        
| - DERECHA                    |        
|                              |
| Objetos Disponibles:         |
| - #04 / Pan                  |
|   Peso: 1   /  Puntos: 2     |
|                              |
+------------------------------+

+------------------------------+
| JUGADOR                      |
+------------------------------+
| (Inventario Vacio)           |
| Peso Total: 0                |
| Puntaje Acumulado: 0         |
| Tiempo Restante: 9           |
+------------------------------+

========================================
1) Recoger Item(s)
2) Descartar Item(s)
3) Avanzar
4) Reiniciar Partida
5) Salir del Juego
========================================
Ingrese su opcion: 4
Volviendo a cargar el Laberinto...
Laberinto cargado exitosamente.     
La Partida se Reincio.
Presione una tecla para continuar...
```
> Al confirmar la opción, el juego reinicia todo el estado del jugador, incluyendo el inventario, puntaje acumulado, tiempo restante y ubicación. Esta función es útil si el jugador queda atascado o desea empezar desde cero para mejorar su desempeño.

#### 🏠 Salir del Juego.
Para cerrar completamente la aplicación, el jugador debe seleccionar la **opción 5** en el menú principal. Esta acción finaliza la ejecución del programa y cierra el sistema de forma definitiva.
```
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
5) Salir del Juego
========================================
Ingrese su opcion: 5
Presione una tecla para continuar...
```
> Se recomienda asegurarse de haber finalizado cualquier partida antes de salir, ya que esta acción cerrará por completo el juego.

#### 🏁 Si el jugador llega al final del laberinto.
Por un lado si el jugador alcanza con éxito la salida del laberinto, se mostrará el siguiente mensaje:
```
FIN - Has llegado a la Salida
Inventario final:
  #08 - Moneda (Peso: 1, Puntos: 2)
  #12 - Rubi (Peso: 5, Puntos: 20)
  #13 - Mapa (Peso: 1, Puntos: 10)
Puntaje final: 32
Presione una tecla para continuar...
```
> ¡Felicidades! Ahora puedes planear una mejor estrategia para superar tu puntaje en la próxima partida.

En caso contrario, si no se llega al final del laberinto, se mostrará un mensaje de derrota:
```
DERROTA - Se ha agotado el tiempo
Inventario final:
  #08 - Moneda (Peso: 1, Puntos: 2)
  #12 - Rubi (Peso: 5, Puntos: 20)
  #13 - Mapa (Peso: 1, Puntos: 10)
Puntaje final: 32
Presione una tecla para continuar...
```
> El tiempo ha terminado. ¡Inténtalo de nuevo utilizando una estrategia más eficiente!
#### 👥 Modo Multijugador.
para el modo multijugador se deberá seleccionar desde el menú principal la opcion 3
```
+--------------------------------------+
|              GraphQuest              |
+--------------------------------------+
| 1) Cargar Laberinto                  |
| 2) Iniciar Partida: Solitario        |
| 3) Iniciar Partida: Multijugador     |
+--------------------------------------+
Ingrese su opcion: 3
```
el juego es por turnos de jugador 1 y jugador 2
```
>>> TURNO DE JUGADOR 1 <<<

========================================
1) Recoger Item(s)
2) Descartar Item(s)
3) Avanzar
4) Reiniciar Partida
5) Volver al Menu Principal
========================================
Ingrese su opcion: _
```
cada jugador tiene su propio inventario, items, peso, tiempo, camino.
```
>>> TURNO DE JUGADOR 2 <<<

========================================
1) Recoger Item(s)
2) Descartar Item(s)
3) Avanzar
4) Reiniciar Partida
5) Volver al Menu Principal
========================================
Ingrese su opcion: _
```
alfinal de la partida se mostrará quien fue el ganador.

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