# Tarea 1: Calcular Pi usando pthreads en C.
## Descripción
En esta tarea se propone calcular el valor de π utilizando el método de Monte Carlo. Se generan puntos aleatorios en un cuadrado de lado 1 y se cuenta cuántos de estos puntos caen dentro de un círculo de radio 1. El valor de π se puede aproximar mediante una fórmula específica. Se utiliza la biblioteca pthread en C para paralelizar el cálculo de π.

## Archivos y ejecución

- ### **calcPi_pthread_1.1.c** 
    ***(El código del PDF pero sin modificar)*** 
    
    Este código implementa una aproximación paralela del valor de π usando el método de Monte Carlo. El programa acepta dos argumentos: el número total de puntos a lanzar y el número de hilos a utilizar. Divide el total de puntos entre los hilos, donde cada hilo lanza sus puntos en un cuadrado de lado 1 y cuenta cuántos puntos caen dentro del círculo de radio 1 inscripto en ese cuadrado. La función `throw_darts` se encarga de esta tarea sin protección de mutex para `points_inside_circle`, lo que puede causar problemas de concurrencia. Finalmente, el programa calcula el valor de π basado en la proporción de puntos dentro del círculo y lo imprime. Actualmente, el paralelismo no está implementado correctamente, ya que `pthread_create` no se usa para crear los hilos.

    Ejecutar con:
    ```bash
        make ARGS="calcPi_pthread_1.1.c [#puntos] [#hilos]"
    ```
  
- ### **calcPi_pthread_1.2.1.c**     
    ***(No protejan la variable points_inside_circle con un mutex)*** 
    
    Este código en C utiliza múltiples hilos para estimar el valor de pi mediante el método de Monte Carlo. Cada hilo genera puntos aleatorios dentro de un cuadrado y cuenta cuántos caen dentro de un círculo inscrito en dicho cuadrado. Los resultados de cada hilo se envían al hilo principal a través de una cola segura para concurrencia implementada con una estructura de nodos enlazados, mutex y variables de condición. El hilo principal recopila los puntos de todos los hilos y calcula el valor de pi.

    Ejecutar con: 
    ```bash
        make ARGS="calcPi_pthread_1.2.1.c [#puntos] [#hilos]"
    ```
  
- ### **calcPi_pthread_1.2.2.c**
    ***(Protejan la variable points_inside_circle con un mutex dentro del ciclo for)***

    Este código en C implementa el cálculo paralelo del valor aproximado de π utilizando el método de Monte Carlo. Primero, se obtienen el número total de puntos a lanzar y el número de hilos desde los argumentos de línea de comandos, verificando restricciones como el límite máximo de hilos y la divisibilidad uniforme de los puntos entre los hilos. Cada hilo genera puntos aleatorios dentro de un cuadrado unitario y utiliza un mutex para proteger la variable que cuenta cuántos puntos caen dentro de un círculo unitario, asegurando la consistencia de los datos compartidos. Después de que todos los hilos completan sus cálculos, se calcula π y se muestra el resultado.

    Ejecutar con: 
    ```bash
        make ARGS="calcPi_pthread_1.2.2.c [#puntos] [#hilos]"
    ```

- ### **calcPi_pthread_1.2.3.c**
    ***(Protejan la variable points_inside_circle con un mutex fuera del ciclo for. En lugar de incrementar la variable global points_inside_circle dentro del ciclo, actualicen una variable local y al final del ciclo incrementen la variable global)***

    Este código en C implementa el cálculo paralelo del valor aproximado de π utilizando hilos. Recibe como argumentos de línea de comandos el número total de puntos y el número de hilos a utilizar. Cada hilo genera puntos aleatorios en un cuadrado unitario y cuenta cuántos caen dentro de un círculo unitario. La suma de estos puntos dentro del círculo se protege con un mutex para evitar condiciones de carrera. Al finalizar todos los hilos, se calcula la aproximación de π y se imprime el resultado.

    Ejecutar con: 
    ```bash
        make ARGS="calcPi_pthread_1.2.3.c [#puntos] [#hilos]"
    ```

- ### **calcPi_pthread_1.2.4.c**
    ***(Similar a 3, pero no actualicen points_inside_circle dentro de throw_darts. Retornen la cantidad de puntos dentro del círculo (usando un falso puntero) y hagan que el hilo principal incremente la variable global)***

    Este código en C implementa el cálculo paralelo del valor aproximado de π utilizando hilos. Recibe como argumentos el número total de puntos y el número de hilos a utilizar. Cada hilo genera puntos aleatorios dentro de un cuadrado unitario y cuenta cuántos de estos puntos caen dentro de un círculo unitario. En lugar de usar un mutex para proteger la variable compartida `points_inside_circle`, cada hilo cuenta sus propios puntos dentro del círculo y devuelve este valor al hilo principal, que luego suma todos estos valores para obtener el total de puntos dentro del círculo. Finalmente, se calcula la aproximación de π basándose en la proporción de puntos dentro del círculo y el total de puntos generados, y se imprime el resultado.

    Ejecutar con: 
    ```bash
        make ARGS="calcPi_pthread_1.2.4.c [#puntos] [#hilos]"
    ```

- ### **calcPi_pthread_1.2.5.c**
    ***(Usen operaciones atómicas para incrementar la variable points_inside_circle)***

    El programa calcula una aproximación de π utilizando múltiples hilos. Recibe como argumentos el número total de puntos y el número de hilos a utilizar. Cada hilo genera puntos aleatorios dentro de un cuadrado unitario y cuenta cuántos de estos puntos caen dentro de un círculo unitario. En lugar de usar un mutex para proteger la variable compartida `points_inside_circle`, se usa una variable atómica `points_inside_circle` que permite incrementar el contador de manera segura y concurrente desde múltiples hilos sin necesidad de bloqueo explícito. Cada hilo cuenta sus propios puntos dentro del círculo y devuelve este valor al hilo principal, que luego suma todos estos valores de manera atómica. Finalmente, se calcula la aproximación de π basándose en la proporción de puntos dentro del círculo y el total de puntos generados, y se imprime el resultado.

    Ejecutar con: 
    ```bash
        make ARGS="calcPi_pthread_1.2.5.c [#puntos] [#hilos]"
    ```