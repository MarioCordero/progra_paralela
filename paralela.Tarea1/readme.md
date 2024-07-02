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
        make ARGS="calcularPImsg01.2.1.c [#puntos] [#hilos]"
    ```
  
- ### **calcPi_pthread_1.2.2.c**
    ***(Protejan la variable points_inside_circle con un mutex dentro del ciclo for.)***

    Este código en C implementa el cálculo paralelo del valor aproximado de π utilizando el método de Monte Carlo. Primero, se obtienen el número total de puntos a lanzar y el número de hilos desde los argumentos de línea de comandos, verificando restricciones como el límite máximo de hilos y la divisibilidad uniforme de los puntos entre los hilos. Cada hilo genera puntos aleatorios dentro de un cuadrado unitario y utiliza un mutex para proteger la variable que cuenta cuántos puntos caen dentro de un círculo unitario, asegurando la consistencia de los datos compartidos. Después de que todos los hilos completan sus cálculos, se calcula π y se muestra el resultado.

    Ejecutar con: 
    ```bash
        make ARGS="calcPi_pthread_1.2.2.c [#puntos] [#hilos]"
    ```

- ### **calcularPImsg01.2.3.c**     
    Este código en C implementa una estimación del valor de pi utilizando el método de Monte Carlo distribuido en múltiples hilos. Cada hilo genera puntos aleatorios dentro de un cuadrado y cuenta cuántos caen dentro de un círculo inscrito. Los resultados de cada hilo se envían al hilo principal a través de un pipe, donde se suman para calcular pi.

    Ejecutar con: 
    ```bash
        make ARGS="calcularPImsg01.2.3.c [#puntos] [#hilos]"
    ```

- ### **calcularPImsg01.2.4.c**    
    Este código en C implementa una estimación del valor de pi utilizando el método de Monte Carlo distribuido en múltiples hilos. Cada hilo genera puntos aleatorios dentro de un cuadrado y cuenta cuántos caen dentro de un círculo inscrito. Los resultados de cada hilo se almacenan dinámicamente en un arreglo y luego se suman para calcular pi en el hilo principal. El programa gestiona la sincronización entre hilos utilizando mutexes para evitar condiciones de carrera.

    Ejecutar con: 
    ```bash
        make ARGS="calcularPImsg01.2.4.c [#puntos] [#hilos]"
    ```