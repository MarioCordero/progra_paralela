# Practica 1: Programación Paralela y Concurrente - Uso de Fork en C
## Descripción
Este proyecto se enfoca en explorar el uso de la llamada al sistema fork en programas en C para crear procesos hijos. Se realizan varios ejercicios prácticos para entender cómo se comportan los procesos padre e hijo, así como para analizar el manejo de memoria y la creación de múltiples procesos.

## Archivos y ejecución
- ### **practica-01-fork-01.c**
  
    Programa que crea un proceso hijo para imprimir mensajes en pantalla.

    Ejecutar con: 
    ```bash
        make ARGS="practica-01-fork-01.c"
    ```
- ### **practica-01-fork-02.c**
 
    Programa que simula una tarea de cómputo pesada usando la función sleep.

    Ejecutar con: 
    ```bash
        make ARGS="practica-01-fork-02.c"
    ```
- ### **practica-01-fork-03.c**

    Programa que espera a que el proceso hijo termine antes de que el proceso padre finalice.

    Ejecutar con: 
    ```bash
        make ARGS="practica-01-fork-03.c"
    ```
- ### **practica-01-fork-04.c**

    Programa que crea varios procesos hijos utilizando un ciclo for.

    Ejecutar con: 
    ```bash
        make ARGS="practica-01-fork-04.c"
    ```
- ### **practica-01-fork-05.c**
    
    Programa que explora el comportamiento de las variables en procesos padre e hijo.

    Ejecutar con: 
    ```bash
        make ARGS="practica-01-fork-05.c"
    ```
- ### **practica-01-fork-06.c**
    
    Programa que analiza si las direcciones de memoria son las mismas en procesos padre e hijo.

    Ejecutar con: 
    ```bash
        make ARGS="practica-01-fork-06.c"
    ```
- ### **practica-01-fork-07.c**

    Programa que investiga cuánta memoria se gasta al crear múltiples procesos hijos.

    Ejecutar con: 
    ```bash
        make ARGS="practica-01-fork-07.c"
    ```
- ### **practica-01-fork-08.c**
    
    Reduzcan total_forks a la cantidad de gigabytes de memoria RAM LIBRES en su computadora.

    Ejecutar con: 
    ```bash
        make ARGS="practica-01-fork-08.c"
    ```

- ### **practica-01-fork-09.c**
    
    Este código en C crea un proceso padre que inicializa un mensaje y luego realiza un bucle para crear ocho procesos hijos mediante la llamada fork(). Cada hijo modifica el mensaje asignándole un saludo único, después borra parte de su contenido y muestra la dirección y el valor del mensaje. Luego, cada hijo espera 10 segundos antes de terminar. El proceso padre espera a que todos los hijos terminen (wait()), imprime un mensaje final y muestra el contenido final del mensaje, que refleja las últimas modificaciones realizadas por los hijos..
    
    Ejecutar con: 
    ```bash
        make ARGS="practica-01-fork-09.c"
    ```