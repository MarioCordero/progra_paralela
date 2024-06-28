package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

// Número de fumadores
const numSmokers = 3

// Estructura para representar los ingredientes
type Ingredient int

const (
	Tobacco Ingredient = iota
	Paper
	Matches
)

// Nombres de los ingredientes para imprimir
var ingredientNames = []string{"Tobacco", "Paper", "Matches"}

// Canal para cada ingrediente
var ingredientChannels [3]chan struct{}

// Canal para el agente
var agentChannel = make(chan struct{})

// WaitGroup para esperar a que todos los fumadores terminen
var wg sync.WaitGroup

// Función del agente
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

// Función del fumador
func smoker(id int, has Ingredient) {
	// Cada que se ejecute el smoker() se decremente la variable de espera
	defer wg.Done()
	for {
		// Un select para administrar cada el primer ingrediente que tengamos o no tengamos
		select {
			// Tengo un ingrediente
			case <-ingredientChannels[(has+1)%3]:
				// Un segundo select para administrar el segundo ingredientes que tengamos o no tengamos
				select {

					case <-ingredientChannels[(has+2)%3]:
						// El fumador con x ingrediente agarra los 2 ingredientes disponibles y fuma
						fmt.Printf("\nSmoker with %s is smoking.\n", ingredientNames[has])

						// El segundo de pausa que simula el fumado
						time.Sleep(time.Second) 

						// Avisar al agente que se terminó de fumar
						agentChannel <- struct{}{}

					// Caso default, si no tengo ese segundo ingrediente, dejo mi ingrediente en la mesa
					default:
						// Envío la señal al canal de que está disponible porque no pude fumar
						ingredientChannels[(has+1)%3] <- struct{}{}
				}
		}
	}
}

func main() {
	rand.Seed(time.Now().UnixNano())

	// Inicializar los canales
	for i := range ingredientChannels {
		// Hacer los canales con buffer de tamaño 1
		ingredientChannels[i] = make(chan struct{}, 1)
	}

	// La cantidad de fumadores
	wg.Add(3)
	
	// Poner a correr al agente
	go agent()

	// Iniciar el proceso con una señal al agente
	agentChannel <- struct{}{}

	// Iniciar las goroutines de los fumadores
	for i := 0; i < numSmokers; i++ {
		
		// Añadir una espera cada que se da un ingrediente
		// Los fumadores van a estar esperando la señal del agente
		// Se le da a cada fumador un
		go smoker(i, Ingredient(i))

	}

	// Esperar a que los fumadores terminen (nunca sucede en esta simulación)
	wg.Wait()
}