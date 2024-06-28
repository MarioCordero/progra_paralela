# Problema de los Fumadores, implementado en GO

Este proyecto implementa el clásico problema de sincronización de los fumadores utilizando el lenguaje de programación Go.

## Descripción

El problema de los fumadores es un problema de sincronización entre procesos en el que hay tres fumadores y un agente. Cada fumador necesita dos de los tres ingredientes (tabaco, papel, fósforos) para hacer un cigarrillo y fumar. El agente coloca aleatoriamente dos ingredientes sobre la mesa y el fumador que tiene el tercer ingrediente toma los dos ingredientes de la mesa, hace un cigarrillo y lo fuma. Luego, el proceso se repite.

## Requisitos:

1. Tener instalado Go
2. Tener un entorno Linux
3. Tener instalado Makefile

## Ejecución del Código

Para ejecutar este proyecto, dentro de la carpeta del proyecto

```sh
    make
```

## Estructura del Código

El código se organiza en varias partes principales:

1. **Constantes y Tipos**:
    - **Número de Fumadores**:
        ```go
        const numSmokers = 3
        ```
    - **Definición de Ingredientes**: Se define un tipo enumerado `Ingredient` para representar los ingredientes.
        ```go
        type Ingredient int

        const (
            Tobacco Ingredient = iota
            Paper
            Matches
        )
        ```
    - **Nombres de los Ingredientes**: Un arreglo para imprimir los nombres de los ingredientes.
        ```go
        var ingredientNames = []string{"Tobacco", "Paper", "Matches"}
        ```

2. **Canales**:
    - **Canales para Ingredientes**: Un arreglo de canales para la comunicación entre el agente y los fumadores.
        ```go
        var ingredientChannels [3]chan struct{}
        ```
    - **Canal para el Agente**: Un canal para la comunicación desde los fumadores hacia el agente.
        ```go
        var agentChannel = make(chan struct{})
        ```

3. **WaitGroup**:
    - **WaitGroup para Sincronización**: Un `sync.WaitGroup` para esperar a que todos los fumadores terminen.
        ```go
        var wg sync.WaitGroup
        ```

4. **Funciones**:
    - **Función del Agente**: Simula el comportamiento del agente que coloca ingredientes en la mesa.
        ```go
        func agent() {
            for {
                // Esperar señal para poner ingredientes
                <-agentChannel

                // Seleccionar dos ingredientes aleatorios
                ingredient1 := rand.Intn(numSmokers)
                ingredient2 := (ingredient1 + rand.Intn(numSmokers-1) + 1) % numSmokers

                fmt.Printf("Agent puts %s and %s on the table.\n", ingredientNames[ingredient1], ingredientNames[ingredient2])

                // Señalar a los fumadores que los ingredientes están en la mesa
                ingredientChannels[ingredient1] <- struct{}{}
                ingredientChannels[ingredient2] <- struct{}{}
            }
        }
        ```
    - **Función del Fumador**: Simula el comportamiento de los fumadores, esperando los ingredientes necesarios y fumando.
        ```go
        func smoker(id int, has Ingredient) {
            defer wg.Done() // Decrementar el contador del WaitGroup cuando esta goroutine termine.
            for {
                select {
                    case <-ingredientChannels[(has+1)%3]:
                        select {
                            case <-ingredientChannels[(has+2)%3]:
                                fmt.Printf("\nSmoker with %s is smoking.\n", ingredientNames[has])
                                time.Sleep(time.Second) // Simula el tiempo de fumar
                                agentChannel <- struct{}{}
                            default:
                                ingredientChannels[(has+1)%3] <- struct{}{}
                        }
                }
            }
        }
        ```

5. **Función Principal (`main`)**:
    - **Inicialización**: Inicializa los canales y lanza las goroutines para el agente y los fumadores.
        ```go
        func main() {
            rand.Seed(time.Now().UnixNano())

            // Inicializar los canales
            for i := range ingredientChannels {
                ingredientChannels[i] = make(chan struct{}, 1) // Hacer los canales con buffer de tamaño 1
            }

            wg.Add(numSmokers)

            // Poner a correr al agente
            go agent()

            // Iniciar el proceso con una señal al agente
            agentChannel <- struct{}{}

            // Iniciar las goroutines de los fumadores
            for i := 0; i < numSmokers; i++ {
                go smoker(i, Ingredient(i))
            }

            // Esperar a que los fumadores terminen (nunca sucede en esta simulación)
            wg.Wait()
        }
        ```

### Descripción del Código

- **Constantes y Tipos**: Definen los ingredientes y el número de fumadores.
- **Canales**: Se utilizan para la comunicación entre el agente y los fumadores.
- **WaitGroup**: Permite sincronizar la terminación de las goroutines de los fumadores.
- **Funciones**:
  - `agent()`: Coloca dos ingredientes aleatorios en la mesa y notifica a los fumadores.
  - `smoker(id int, has Ingredient)`: Cada fumador espera los dos ingredientes que necesita, simula el fumar y notifica al agente cuando termina.
- **Función Principal (`main`)**: Inicializa los canales, lanza las goroutines y gestiona la sincronización.

Este código simula el problema de los fumadores, donde el agente pone dos ingredientes en la mesa y los fumadores intentan tomar los ingredientes necesarios para fumar.