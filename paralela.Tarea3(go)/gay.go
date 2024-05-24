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
var ingredientChannels [numSmokers]chan struct{}

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
	defer wg.Done()
	for {
		// Esperar a que estén los ingredientes que necesita
		<-ingredientChannels[(has+1)%numSmokers]
		<-ingredientChannels[(has+2)%numSmokers]

		// Fumar (simulación con sleep)
		fmt.Printf("Smoker with %s is smoking.\n", ingredientNames[has])
		time.Sleep(time.Second)

		// Señalar al agente que termine y ponga nuevos ingredientes
		agentChannel <- struct{}{}
	}
}

func main() {
	rand.Seed(time.Now().UnixNano())

	// Inicializar los canales
	for i := range ingredientChannels {
		ingredientChannels[i] = make(chan struct{})
	}

	// Añadir fumadores al WaitGroup
	wg.Add(numSmokers)

	// Iniciar las goroutines de los fumadores
	for i := 0; i < numSmokers; i++ {
		go smoker(i, Ingredient(i))
	}

	// Iniciar la goroutine del agente
	go agent()

	// Iniciar el proceso con una señal al agente
	agentChannel <- struct{}{}

	// Esperar a que los fumadores terminen (nunca sucede en esta simulación)
	wg.Wait()
}
