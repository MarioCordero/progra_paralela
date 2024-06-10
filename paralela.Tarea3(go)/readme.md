# Problema de los Fumadores

Este proyecto implementa el clásico problema de sincronización de los fumadores utilizando el lenguaje de programación Go.

## Descripción

El problema de los fumadores es un problema de sincronización entre procesos en el que hay tres fumadores y un agente. Cada fumador necesita dos de los tres ingredientes (tabaco, papel, fósforos) para hacer un cigarrillo y fumar. El agente coloca aleatoriamente dos ingredientes sobre la mesa y el fumador que tiene el tercer ingrediente toma los dos ingredientes de la mesa, hace un cigarrillo y lo fuma. Luego, el proceso se repite.

## Ejecución del Código

Para ejecutar este proyecto, sigue los siguientes pasos:

### Uso del Makefile

1. **Compilar y ejecutar el programa**:
    ```sh
    make
    ```

## Notas

- El programa está diseñado para correr indefinidamente, simulando el comportamiento continuo de los fumadores y el agente.
- La implementación utiliza canales con buffer para evitar bloqueos y asegurar la correcta sincronización entre las goroutines.

## Autor

- Mario Cordero C22306