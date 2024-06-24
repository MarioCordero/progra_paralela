# Práctica #5 Programación Paralela y Concurrente

En esta práctica de la asignatura de Programación Paralela y Concurrente de la Universidad de Costa Rica, se exploran las instrucciones SIMD (Single Instruction, Multiple Data) en C utilizando intrinsics y se investiga la autovectorización con gcc en Linux. El profesor a cargo de la práctica es Esteban Rodríguez Betancourt.

## Ejecución
Para compilar el programa, se puede utilizar el comando:

```sh
make ARGS="[nombre del archivo]"
```

Y en "nombre del archivo" debe de poner el nombre del archivo '.c' a compilar y ejecutar

## Ejercicios y nombres de los archivos

### Ejercicio 1: Introducción a SIMD (InstruccionesSIMD01.c)
Se debe crear un programa en C que sume dos vectores de enteros utilizando intrinsics SIMD. Se utilizan las instrucciones `_mm_loadu_si128`, `_mm_add_epi32` y `_mm_storeu_si128`.

### Ejercicio 2: Resta de vectores (InstruccionesSIMD02.c)
Se modifica el programa del ejercicio 1 para restar dos vectores de enteros utilizando la instrucción `_mm_sub_epi32`.

### Ejercicio 3: Producto punto (InstruccionesSIMD03.c)
Se calcula el producto punto de dos vectores de enteros usando SIMD. Se utiliza la instrucción `_mm_mullo_epi32` y se realiza la reducción final con código en C típico.

### Ejercicio 4: Carga y almacenamiento alineados (InstruccionesSIMD04.c)
Se modifica el código del ejercicio 1 para cambiar las instrucciones de carga y almacenamiento por versiones alineadas. Se utiliza `_mm_load_si128` y `_mm_store_si128`, asegurando que los datos estén alineados a 16 bits.

### Ejercicio 5: Multiplicación de matrices 2x2 (InstruccionesSIMD05.c)
Se realiza la multiplicación de dos matrices 2x2 utilizando intrinsics SIMD. Se utilizan las instrucciones `_mm_set_epi32`, `_mm_mullo_epi32` y `_mm_extract_epi32`.

### Ejercicio 6: Mayor elemento de un array (InstruccionesSIMD06.c)
```sh
make ARGS="InstruccionesSIMD05.c" && objdump -d compile_general
```
Se crean dos funciones para calcular el mayor elemento de un array de enteros de 32 bits, una utilizando instrucciones SIMD y otra con un for tradicional. Se utilizan instrucciones como `_mm_set1_epi32`, `_mm_load_si128`, `_mm_max_epi32` y `_mm_storeu_si128`.

### Ejercicio 7: Multiplicación escalar (InstruccionesSIMD07.c)
Se implementa la multiplicación por un escalar en dos versiones, una utilizando SIMD y otra tradicional. Se emplean instrucciones como `_mm_loadu_si128`, `_mm_set1_epi32`, `_mm_mullo_epi32` y `_mm_storeu_si128`.

### Ejercicio 8: Autovectorización (InstruccionesSIMD08.c)
Se compila un código dado con diferentes opciones en gcc para observar la autovectorización. Se analizan las diferencias en el código generado con `objdump -d`.

### Ejercicio 9: Reducción paralela (InstruccionesSIMD09.c)
Se investiga y se implementa la función `_mm_hadd_epi32` para sumar todos los elementos de un array de forma paralela. Se utilizan instrucciones como `_mm_add_epi32` y `_mm_hadd_epi32`.

## Instrucciones Generales
- Cada ejercicio debe ser implementado en un archivo diferente.
- Se pueden crear archivos Makefile para facilitar la compilación.
- Se debe documentar cómo se debe compilar cada archivo.