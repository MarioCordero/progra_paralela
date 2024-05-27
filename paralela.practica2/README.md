# Practica 2: Uso de pthread en Programación Paralela y Concurrente
Mario Cordero Aguilar

C22306

## Descripción
Esta tarea se centra en el uso de la biblioteca pthread en C para crear programas que hagan uso de múltiples hilos de ejecución. Se exploran conceptos como la creación de hilos, el uso compartido de memoria, la detección de errores de sincronización y la sincronización de hilos con mutex.

## Archivos
- **pthread01.c**: Programa que crea un hilo para imprimir un mensaje en la consola.
- **pthread02.c**: Programa que muestra el uso compartido de memoria entre hilos y presenta un problema de sincronización.
- **pthread03.c**: Programa que soluciona el problema de sincronización al realizar incrementos de forma atómica.
- **pthread03atomic.c**: Programa que utiliza la biblioteca stdatomic.h para realizar operaciones atómicas.
- **pthread04args.c**: Programa que muestra cómo usar un mutex para sincronizar el acceso a una variable compartida.

## Ejecución
Para compilar y ejecutar los programas, se puede utilizar el comando `make` para compilar y ejecutar. Recuerde cambiar el nombre del archivo a compilar en el Makefile

## Reportes
Cada programa tiene preguntas específicas que se deben responder después de ejecutarlos. Los reportes se basan en la observación de los resultados obtenidos al ejecutar los programas.

## Observaciones
- Se recomienda ejecutar los programas varias veces para observar diferentes resultados y comprender mejor los conceptos.
- Es importante prestar atención a los problemas de sincronización y utilizar herramientas como helgrind y ThreadSanitizer para detectar errores.
- Se debe tener cuidado al trabajar con memoria compartida y asegurarse de utilizar mecanismos de sincronización adecuados para evitar problemas de concurrencia.