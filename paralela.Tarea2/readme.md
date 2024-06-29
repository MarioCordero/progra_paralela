# Tarea 2: Uso de pthread en Programación Paralela y Concurrente
## Descripción
En esta tarea se aborda el uso de la biblioteca pthread en C para desarrollar programas que aprovechen la programación paralela y concurrente. Se explorarán conceptos como la creación de hilos, la sincronización de hilos, el uso compartido de memoria por medio de envio de mensajes y la resolución de problemas de concurrencia.

## Archivos y ejecución

- ### **calcularPImsg01.c** 
    Este código en C simula el método de Monte Carlo para estimar el valor de pi lanzando dardos aleatoriamente dentro de un cuadrado y contando cuántos caen dentro de un círculo inscrito, usando múltiples hilos para mejorar la eficiencia mediante paralelismo.    

    Ejecutar con:
    ```bash
        make ARGS="calcularPImsg01.c [#puntos] [#hilos]"
    ```
  
- ### **calcularPImsg01.2.1.c**     
    Este código en C utiliza múltiples hilos para estimar el valor de pi mediante el método de Monte Carlo. Cada hilo genera puntos aleatorios dentro de un cuadrado y cuenta cuántos caen dentro de un círculo inscrito en dicho cuadrado. Los resultados de cada hilo se envían al hilo principal a través de una cola segura para concurrencia implementada con una estructura de nodos enlazados, mutex y variables de condición. El hilo principal recopila los puntos de todos los hilos y calcula el valor de pi.

    Ejecutar con: 
    ```bash
        make ARGS="calcularPImsg01.2.1.c [#puntos] [#hilos]"
    ```
  
- ### **calcularPImsg01.2.2.c**     
    Este código en C estima el valor de pi usando el método de Monte Carlo, creando múltiples hilos que generan puntos aleatorios dentro de un cuadrado y cuentan cuántos caen dentro de un círculo inscrito, enviando los resultados al hilo principal a través de una cola de mensajes. El hilo principal recopila estos mensajes, calcula pi.

    Ejecutar con: 
    ```bash
        make ARGS="calcularPImsg01.2.2.c [#puntos] [#hilos]"
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