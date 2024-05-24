# Practica 1: Programación Paralela y Concurrente - Uso de Fork

Mario Cordero Aguilar

C22306

## Descripción
Este proyecto se enfoca en explorar el uso de la llamada al sistema fork en programas en C para crear procesos hijos. Se realizan varios ejercicios prácticos para entender cómo se comportan los procesos padre e hijo, así como para analizar el manejo de memoria y la creación de múltiples procesos.

## Archivos
- **practica-01-fork-01.c**: Programa que crea un proceso hijo para imprimir mensajes en pantalla.
- **practica-01-fork-02.c**: Programa que simula una tarea de cómputo pesada usando la función sleep.
- **practica-01-fork-03.c**: Programa que espera a que el proceso hijo termine antes de que el proceso padre finalice.
- **practica-01-fork-04.c**: Programa que crea varios procesos hijos utilizando un ciclo for.
- **practica-01-fork-06.c**: Programa que explora el comportamiento de las variables en procesos padre e hijo.
- **practica-01-fork-07.c**: Programa que analiza si las direcciones de memoria son las mismas en procesos padre e hijo.
- **practica-01-fork-08.c**: Programa que investiga cuánta memoria se gasta al crear múltiples procesos hijos.
- **practica-01-fork-09.c**: Reduzcan total_forks a la cantidad de gigabytes de memoria RAM LIBRES en su computadora.

## Ejecución
Para compilar y ejecutar los programas, se puede utilizar el comando `make` para compilar y ejecutar. Recuerde cambiar el nombre del archivo a compilar en el Makefile

## Reportes
Cada programa tiene preguntas específicas que se deben responder después de ejecutarlos. Los reportes se basan en la observación de los resultados obtenidos al ejecutar los programas.

## Observaciones
- Es importante recordar que en un programa real se deben agregar validaciones que no se incluyeron en estos ejercicios.
- Se hace énfasis en la importancia de liberar la memoria asignada con `free` al finalizar un proceso.
- Se recomienda ejecutar los programas con precaución, especialmente en el ejercicio 9 donde se manipula la asignación de memoria de forma intensiva.