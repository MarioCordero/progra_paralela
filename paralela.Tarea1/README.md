# Tarea 1: Calcular Pi usando pthreads

Mario Cordero Aguilar

C22306

## Descripción
En esta tarea se propone calcular el valor de π utilizando el método de Monte Carlo. Se generan puntos aleatorios en un cuadrado de lado 1 y se cuenta cuántos de estos puntos caen dentro de un círculo de radio 1. El valor de π se puede aproximar mediante una fórmula específica. Se utiliza la biblioteca pthread en C para paralelizar el cálculo de π.

## Archivos
- **calcPi_pthread**: Programa principal que implementa el cálculo de π en paralelo utilizando pthreads.
- **Makefile**: Archivo para compilar el programa de forma sencilla.

## Ejecución
Para compilar el programa, se puede utilizar el comando `make ARGS="<total_points> <total_threads>"`.

## Reporte de Resultados
Se debe entregar un reporte con las siguientes estrategias de implementación:
1. Implementación original del programa.
2. Implementación modificada para cálculo en paralelo con pthreads.
   - Sin protección de variable points_inside_circle.
   - Protegiendo la variable con un mutex dentro del ciclo for.
   - Protegiendo la variable con un mutex fuera del ciclo for.
   - Actualizando una variable local y luego incrementando la global.
   - Utilizando operaciones atómicas para incrementar la variable.

## Instrucciones Adicionales
- Se recomienda probar el programa con diferentes cantidades de puntos y hilos.
- Se debe describir y corregir los problemas de concurrencia detectados con herramientas como Helgrind o ThreadSanitizer.
- Realizar pruebas de rendimiento con diferentes configuraciones de puntos y hilos.
- Comparar la velocidad de ejecución entre las diferentes implementaciones.

¡Explora el cálculo de π en paralelo y comprende los conceptos de programación concurrente con pthreads en esta tarea!
