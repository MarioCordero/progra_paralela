# Problema de los Fumadores

Este proyecto implementa el clásico problema de sincronización de los fumadores utilizando el lenguaje de programación Go.

## Descripción

El problema de los fumadores es un problema de sincronización entre procesos en el que hay tres fumadores y un agente. Cada fumador necesita dos de los tres ingredientes (tabaco, papel, fósforos) para hacer un cigarrillo y fumar. El agente coloca aleatoriamente dos ingredientes sobre la mesa y el fumador que tiene el tercer ingrediente toma los dos ingredientes de la mesa, hace un cigarrillo y lo fuma. Luego, el proceso se repite.

## Estructura del Código

El código se organiza en varias partes principales:

1. **Constantes y Tipos**:
    - Definición de los ingredientes y sus nombres.

2. **Canales**:
    - Canales para la comunicación entre el agente y los fumadores.

3. **Funciones**:
    - `agent()`: Función que simula el comportamiento del agente.
    - `smoker(id int, has Ingredient)`: Función que simula el comportamiento de los fumadores.

4. **Función Principal (`main`)**:
    - Inicializa los canales y lanza las goroutines para el agente y los fumadores.

## Ejecución del Código

Para ejecutar este proyecto, sigue los siguientes pasos:

1. **Clona el repositorio**:
    ```sh
    git clone <URL_DEL_REPOSITORIO>
    cd <NOMBRE_DEL_DIRECTORIO>
    ```

2. **Compila y ejecuta el programa**:
    ```sh
    go run <NOMBRE_DEL_ARCHIVO>.go
    ```

    Donde `<NOMBRE_DEL_ARCHIVO>` es el nombre del archivo que contiene el código del problema de los fumadores (por ejemplo, `smokers_problem.go`).

## Makefile

El proyecto incluye un `Makefile` para facilitar las tareas comunes como compilar y ejecutar el programa. Las siguientes reglas están disponibles:

- **build**: Compila el programa.
- **run**: Compila y ejecuta el programa.
- **clean**: Elimina los archivos compilados.

### Uso del Makefile

1. **Compilar el programa**:
    ```sh
    make build
    ```

2. **Ejecutar el programa**:
    ```sh
    make run
    ```

3. **Limpiar archivos compilados**:
    ```sh
    make clean
    ```

## Notas

- El programa está diseñado para correr indefinidamente, simulando el comportamiento continuo de los fumadores y el agente.
- La implementación utiliza canales con buffer para evitar bloqueos y asegurar la correcta sincronización entre las goroutines.

## Autor

- [Tu Nombre]

## Licencia

Este proyecto está licenciado bajo la Licencia MIT - ver el archivo [LICENSE](LICENSE) para más detalles.