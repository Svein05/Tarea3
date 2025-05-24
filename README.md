# 👾 GraphQuest 

## 📌 Descripción:
Este programa ofrece al usuario la posibilidad de jugar **GraphQuest**, una aventura ambientada en un **laberinto compuesto por diversos escenarios interconectados**, donde deberá tomar decisiones y recolectar objetos útiles.

La partida comienza en el escenario **"Entrada principal"**, y el objetivo es llegar al escenario final **"Salida"**, eligiendo cuidadosamente cada ruta y seleccionando qué **ítems** recoger en el camino.

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
- **Recolección** de ítems.
- **Descartar** ítems.
- **Avanzar** al siguiente escenario.
- **Reiniciar** Partida.
- **Salir** del juego.

> #### ⚠️ Problemas Conocidos
> El juego **no guarda el mejor puntaje** ni el historial de partidas anteriores.

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
### 👾 Procedimiento de Ejemplo:
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
Presione una tecla para continuar...
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
| Tiempo Restante: 153          |
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
Tiempo Restante: 14 - 1 = 13
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
Tiempo Restante: 13 - 1 = 12
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
Tiempo Restante: 12 - 1 = 11
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
Estas seguro que deseas reiniciar la partida?
Todo tu progreso se perdera.
 1) Si
 2) No
Ingrese su opcion: 1
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
Estas seguro que deseas salir de la partida?
Todo tu progreso se perdera.
 1) Si
 2) No
Ingrese su opcion: 1
```
> Se recomienda asegurarse de haber finalizado cualquier partida antes de salir, ya que esta acción cerrará por completo el juego.

#### 🏁 Si el jugador llega al final del laberinto.
Si el jugador alcanza con éxito la salida del laberinto, se mostrará el siguiente mensaje:
```
FIN - Has llegado a la Salida
Inventario final:
  #08 - Moneda (Peso: 1, Puntos: 2)
  #12 - Rubi (Peso: 5, Puntos: 20)
  #13 - Mapa (Peso: 1, Puntos: 10)
Puntaje final: 32
Se reiniciara el Laberinto...
Laberinto cargado exitosamente.
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
Se reiniciara el Laberinto...
Laberinto cargado exitosamente.
Presione una tecla para continuar...
```
> Se ha agotado el tiempo. ¡Inténtalo de nuevo utilizando una estrategia más eficiente!
#### 👥 Modo Multijugador.
Para jugar el modo multijugador, se debe seleccionar la **opción 3** desde el menú principal:
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
En este modo, dos jugadores participan por **turnos**. Cada uno cuenta con su **propio** inventario, tiempo restante, peso acumulado, ítems recolectados y ruta individual dentro del laberinto.

Durante el turno de cada jugador, se presenta el siguiente menú de acciones:
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
Al finalizar el turno del Jugador 1, es el turno del Jugador 2:
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
Cuando ambos jugadores **llegan al escenario final** o **se les haya acabado el tiempo**, la partida termina y se muestra un resumen de resultados:
```
========================================
         GraphQuest: Multijugador
========================================

+------------------------------+
| ESCENARIO                    |
+------------------------------+
| Camara secreta               |
|                              |
| Una sala oculta con simbolos |
| raros y un mapa brillante.   |
| Nada que ver con una oficina |
| de gobierno, esto si que es  |
| secreto.                     |
|                              |
| Acciones Posibles:           |
| - IZQUIERDA                  |
| - DERECHA                    |
|                              |
| Objetos Disponibles:         |
| -> #13 / Mapa                |
|    Peso: 1   ,  Puntos: 10   |
|                              |
+------------------------------+

+------------------------------+
| JUGADOR                      |
+------------------------------+
| -> #03 / Cuchillo            |
|    Peso: 1   ,  Puntos: 3    |
|                              |
| Peso Total: 1                |
| Puntaje Acumulado: 3         |
| Tiempo Restante: 9           |
+------------------------------+

>>> TURNO DE JUGADOR 1 <<<

========================================
1) Recoger Item(s)
2) Descartar Item(s)
3) Avanzar
4) Reiniciar Partida
5) Salir del Juego
========================================
Ingrese su opcion: 3

Opciones para Avanzar
 1) IZQUIERDA (Corredor)
 2) DERECHA (Salida)

Elija una opcion (0 para cancelar): 2
+------------------------------+
|    EL JUEGO HA FINALIZADO    |
+------------------------------+

+------------------------------+
| JUGADOR 1                    |
+------------------------------+
| -> #03 / Cuchillo            |
|    Peso: 1   ,  Puntos: 3    |
|                              |
| Puntaje Acumulado: 3         |
| Llego al Final? SI
+------------------------------+

+------------------------------+
| JUGADOR 2                    |
+------------------------------+
| (Inventario Vacio)           |
| Puntaje Acumulado: 0         |
| Llego al Final? SI
+------------------------------+

+------------------------------+
|    EL JUGADOR 1 HA GANADO    |
+------------------------------+
Se reiniciara el Laberinto...
Laberinto cargado exitosamente.
Presione una tecla para continuar...
```

>📝 **Observaciones**:
>- Cada jugador **puede explorar caminos distintos** del laberinto.
>- **Los ítems son únicos**: si un jugador recoge uno, ya no estará disponible para el otro.
>- Si un jugador llega a la salida antes que el otro, debe **esperar** a que el segundo también finalice su recorrido.
>- El **resultado final** depende de múltiples condiciones:
>  - Si uno llega al final y el otro no, **gana quien llegó**.
>  - Si ambos llegan pero con distinto puntaje, **gana quien acumuló más puntos**.
>  - Si ambos llegan y tienen el mismo puntaje, **es un empate**.
>  - Si ninguno llega al final, **no hay ganador**.

## Contribuciones

### Elias Manríquez
- **Desarrollo de la función principal del juego**: Implementó la lógica central de la aplicación, incluyendo la carga del laberinto desde un archivo CSV y la ejecución de la partida tanto en modo solitario como multijugador.

- **Diseño del menú principal**: Creó la estructura de navegación del menú principal, facilitando el acceso a las distintas funcionalidades del juego.

- **Implementación de funciones clave**: Desarrolló funciones esenciales como avanzar entre escenarios, recoger y descartar ítems, reiniciar la partida, y gestionar el tiempo y el inventario.

- **Documentación básica**: Añadió comentarios al código fuente y contribuyó a la elaboración inicial del `README.md`.

> Auto-evaluación: 5/5 (Aporte Excelente)

### Maximiliano Rodríguez
- **Optimización en la carga del laberinto**: Mejoró la eficiencia del proceso de carga desde archivos CSV grandes, asegurando un manejo más rápido y estable.

- **Manejo de errores y validaciones**: Implementó validaciones de entrada del usuario y control de errores para evitar fallos durante la ejecución del juego.

- **Mejoras en la experiencia de usuario**: Refinó la interacción del jugador en la interfaz de texto, con mensajes más claros y un flujo de juego más intuitivo.

- **Redacción final del README**: Redactó y organizó el contenido del archivo `README.md`, documentando detalladamente el funcionamiento, modos de juego y estructura técnica del programa.

> Auto-evaluación: 5/5 (Aporte excelente)