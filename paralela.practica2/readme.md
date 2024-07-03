# Practica 2: Uso de pthread en Programación Paralela y Concurrente en C.
## Descripción
Esta tarea se centra en el uso de la biblioteca pthread en C para crear programas que hagan uso de múltiples hilos de ejecución. Se exploran conceptos como la creación de hilos, el uso compartido de memoria, la detección de errores de sincronización y la sincronización de hilos con mutex.

## Archivos y ejecución
- ### **pthread01.c**
 
    Programa que crea un hilo para imprimir un mensaje en la consola.

    Ejecutar con: 
    ```bash
        make ARGS="pthread01.c"
    ```
- ### **pthread02.c**
  
    Programa que muestra el uso compartido de memoria entre hilos y presenta un problema de sincronización.

    Ejecutar con: 
    ```bash
        make ARGS="pthread02.c"
    ```
- ### **pthread03.c**
  
    Programa que soluciona el problema de sincronización al realizar incrementos de forma atómica.

    Ejecutar con: 
    ```bash
        make ARGS="pthread03.c"
    ```
- ### **pthread03atomic.c**
  
    Programa que utiliza la biblioteca stdatomic.h para realizar operaciones atómicas.

    Ejecutar con: 
    ```bash
        make ARGS="pthread03atomic.c"
    ```
- ### **pthread04args.c**
  
    Este código en C crea 16 hilos que ejecutan una función `sum` donde cada hilo suma dos enteros proporcionados a través de una estructura `arguments` y muestra el resultado. Para garantizar que la operación de suma y la impresión del resultado se realicen sin interferencias entre hilos, se utiliza un mutex para bloquear y desbloquear la sección crítica. El programa inicializa el mutex, crea los hilos pasándoles los argumentos correspondientes, espera a que todos los hilos terminen su ejecución con `pthread_join`, y finalmente destruye el mutex antes de finalizar.

    Ejecutar con: 
    ```bash
        make ARGS="pthread04args.c"
    ```