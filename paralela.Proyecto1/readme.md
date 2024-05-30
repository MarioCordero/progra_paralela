# Proyecto de Conteo de palabras usando hilos



## Equipo
- Nathalie Alfaro Quesada B90221
- Mario Cordero Aguilar C22306




## Colaboracion de cada integrante
- Mario Cordero: Implementación de la lectura del documento, división del trabajo entre threads y documentacion.
- Nathalie Alfaro: Implementación del conteo de palabras, ordenamiento alfabético, POO y documentacion.



## Compilar y ejecutar

El programa esta hecho en WSL/Ubuntu/Linux con el compilador de G++.

- Si va a compilar y ejecutar con Makefile, necesita tener instalado el G++ y el Makefile.

    Pasos para compilar: 
    - `cd paralela.Proyecto1`
    - `make`

- Otra forma de compilar y ejecutar sin Makefile:
    - `cd paralela.Proyecto1`
    - `g++ -o executeme main.cpp`
    - `./executeme < prueba.txt`



## Diseño de su programa

El programa se divide en varias etapas:

1. Lectura del documento desde la entrada estándar.
2. Convertir las palabras a minusculas.
3. Pasarlas al canal.
4. División del trabajo entre threads para procesar el documento.
5. Cada hilo cuenta las palabras de la linea que procesa y las almacena en una tabla hash, la palabra y su cantidad de veces que aparece.
6. Pasar las tablas hash locales a una global para eliminar las coincidencias, pero aumentando su contador.
7. Tomar las claves de la tabal hash global y pasarlas a un vector de tipo string.
8. A dicho vector se le aplica el ordenamiento por mezcla para tener una tabla ordenada alfabeticamente.
9. Imprimir la tabla en orden con sus contadores.



## Problemas encontrados y no reparados

Durante el desarrollo del proyecto, nos encontramos con los siguientes problemas:

- Gestión eficiente de la memoria al procesar archivos grandes.
- Coordinación entre threads para evitar condiciones de carrera.
- Cálculo del tamaño de las variables usadas en el programa.
- Escritura en disco una vez sobrepasado el límite de memoria de las variables usadas en el programa.



## Como usar

Al ejecutar el programa, este ya contiene un archivo txt que va a procesar automaticamente, entonces el resultado en la terminal es una tabla en orden alfabetico de la cantidad de veces que aparece cada palabra. Si se desea procesar un texto diferente, pues se debe ir al archivo prueba.txt y reemplazar el texto, luego compilar y ejecutar.



## Funcionalidad implementada

Este proyecto es hecho en C++, el cual consiste en recibir un texto por la entrada estandar que se lee una sola vez y se divide cada linea y se pasa al canal para que cada hilo tome una y la procese. Cabe destacar que todas las palabras se convierten a minusculas despues de leerlas.

Cada hilo hace una tabla hash para su linea, donde cuenta la cantidad de veces que aparece cada palabra sin repetirse.

Cuando los hilos hayan termiando de procesar su linea, se pasan a una tabla hash global y se eliminan las palabras repetidas pero aumentando su contador.

Una vez lista esta tabla hash global, se toman sus claves que serian las palabras, para agregarlas a un vector de su mismo tipo, string, este vector se le aplica el algoritmo de ordenamiento por mezcla para obtener una tabla ordenada alfabeticamente de la manera mas eficiente posible para imprimirla con formato "Palabra: contador" y que sea solo una palabra por linea.

Ademas, se prueba con Valgrind con el texto actual y no se encuentran fugas de memoria.

Tambien, se formatea el codigo con Clang format.
