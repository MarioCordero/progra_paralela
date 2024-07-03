# Práctica #5 Programación Paralela y Concurrente, uso de SIMD en C
## Descripción
En esta práctica de la asignatura de Programación Paralela y Concurrente de la Universidad de Costa Rica, se exploran las instrucciones SIMD (Single Instruction, Multiple Data) en C utilizando intrinsics y se investiga la autovectorización con gcc en Linux.

## Archivos y ejecución

- ### **Ejercicio 1: Introducción a SIMD**

    Se debe crear un programa en C que sume dos vectores de enteros utilizando intrinsics SIMD. Se utilizan las instrucciones `_mm_loadu_si128`, `_mm_add_epi32` y `_mm_storeu_si128`.

    Ejecutar con: 
    ```bash
        make ARGS="InstruccionesSIMD01.c"
    ```
- ### **Ejercicio 2: Resta de vectores**
 
    Se modifica el programa del ejercicio 1 para restar dos vectores de enteros utilizando la instrucción `_mm_sub_epi32`.

    Ejecutar con: 
    ```bash
        make ARGS="InstruccionesSIMD02.c"
    ```
- ### **Ejercicio 3: Producto punto**

    Se calcula el producto punto de dos vectores de enteros usando SIMD. Se utiliza la instrucción `_mm_mullo_epi32` y se realiza la reducción final con código en C típico.

    Ejecutar con: 
    ```bash
        make ARGS="InstruccionesSIMD03.c"
    ```
- ### **Ejercicio 4: Carga y almacenamiento alineados**

    Se modifica el código del ejercicio 1 para cambiar las instrucciones de carga y almacenamiento por versiones alineadas. Se utiliza `_mm_load_si128` y `_mm_store_si128`, asegurando que los datos estén alineados a 16 bits.

    Ejecutar con: 
    ```bash
        make ARGS="InstruccionesSIMD04.c"
    ```
- ### **Ejercicio 5: Multiplicación de matrices 2x2**

    Se realiza la multiplicación de dos matrices 2x2 utilizando intrinsics SIMD. Se utilizan las instrucciones `_mm_set_epi32`, `_mm_mullo_epi32` y `_mm_extract_epi32`.

    Ejecutar con: 
    ```bash
        make ARGS="InstruccionesSIMD05.c"
    ```
- ### **Ejercicio 6: Mayor elemento de un array**

    Se crean dos funciones para calcular el mayor elemento de un array de enteros de 32 bits, una utilizando instrucciones SIMD y otra con un for tradicional. Se utilizan instrucciones como `_mm_set1_epi32`, `_mm_load_si128`, `_mm_max_epi32` y `_mm_storeu_si128`.

    Ejecutar con: 
    ```bash
        make ARGS="InstruccionesSIMD05.c" && objdump -d compile_general
    ```
- ### **Ejercicio 7: Multiplicación escalar**

    Se implementa la multiplicación por un escalar en dos versiones, una utilizando SIMD y otra tradicional. Se emplean instrucciones como `_mm_loadu_si128`, `_mm_set1_epi32`, `_mm_mullo_epi32` y `_mm_storeu_si128`.

    Ejecutar con: 
    ```bash
        make ARGS="InstruccionesSIMD07.c"
    ```
- ### **Ejercicio 8: Autovectorización**

    Se compila un código dado con diferentes opciones en gcc para observar la autovectorización. Se analizan las diferencias en el código generado con `objdump -d`.

    Ejecutar con: 
    ```bash
        make ARGS="InstruccionesSIMD08.c"
    ```
- ### **Ejercicio 9: Reducción paralela**

    Se investiga y se implementa la función `_mm_hadd_epi32` para sumar todos los elementos de un array de forma paralela. Se utilizan instrucciones como `_mm_add_epi32` y `_mm_hadd_epi32`.

    Ejecutar con: 
    ```bash
        make ARGS="InstruccionesSIMD09.c"
    ```