package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

// Número de fumadores
const numSmokers = 3
const maxIterations = 10 // Número máximo de iteraciones antes de finalizar

// Estructura para representar los ingredientes
type Ingrediente int

var globalCounter = 0

// Declaración de constantes
const (
	tabaco   Ingrediente = 0
	papel    Ingrediente = 1
	fosforos Ingrediente = 2
)

// Nombres de los ingredientes para imprimir
var ingredientNames = []string{
	"Tabaco",
	"Papel",
	"Fósforos",
}

// Canales para los ingredientes
var ingredientChannels [numSmokers]chan struct{}

// Canal para el agente
var agentChannel = make(chan struct{}, 1) // Hacer el canal con buffer

// WaitGroup para esperar a que todos los fumadores terminen
var wg sync.WaitGroup

// Mutex para la sincronización
var mutex sync.Mutex

// Estado de los ingredientes en la mesa, empieza con todo en false, diciendo que no hay ningún ingrediente en la mesa
var onTable = [numSmokers]bool{false, false, false}

// Función del agente
func agent() {
	for {
		<-agentChannel
		fmt.Println("\nAgente recibió señal para poner ingredientes en la mesa.\n")

		mutex.Lock()
		if globalCounter >= maxIterations {
			// Señalar el fin del proceso
			mutex.Unlock()
			fmt.Println("Agente ha alcanzado el máximo de iteraciones, finalizando.")
			return
		}

		ingredient1 := rand.Intn(numSmokers)
		ingredient2 := (ingredient1 + rand.Intn(numSmokers-1) + 1) % numSmokers

		if ingredient1 == ingredient2 {
			ingredient2 = (ingredient2 + 1) % numSmokers
		}

		onTable[ingredient1] = true
		onTable[ingredient2] = true

		fmt.Printf("El agente pone [%s] y [%s] en la mesa.\n", ingredientNames[ingredient1], ingredientNames[ingredient2])

		// Aqui enviamos las señales a los canales
		ingredientChannels[ingredient1] <- struct{}{}
		ingredientChannels[ingredient2] <- struct{}{}
		mutex.Unlock()
	}
}

// Función del fumador
func smoker(id int, has Ingrediente) {
	// 		cuando se ejecuta defer wg.Done(), se está indicando que, cuando una goroutine de fumador finalice su trabajo y 
	// esté a punto de retornar, se debe informar al WaitGroup que esa goroutine ha terminado. Esto decrementa el contador 
	// interno del WaitGroup.
	defer wg.Done()
	for {
		fmt.Printf("Fumador con [%s] esperando ingredientes.\n", ingredientNames[has])
		// Aqui esperamos, recibimos las señales de los canales
		<-ingredientChannels[(has+1)%numSmokers]
		<-ingredientChannels[(has+2)%numSmokers]
		fmt.Printf("Fumador con [%s] recibió señal para verificar la mesa.\n", ingredientNames[has])

		mutex.Lock()
		// Este if verifica sí están los ingretiendes en la mesa, ambos ingredientes deben ser "true" para que el fumador pueda proceder a fumar.
		if onTable[(has+1)%numSmokers] && onTable[(has+2)%numSmokers] {
			if globalCounter >= maxIterations {
				// Señalar el fin del proceso
				mutex.Unlock()
				fmt.Printf("Fumador con [%s] ha alcanzado el máximo de iteraciones, finalizando.\n", ingredientNames[has])
				return
			}

			// Iterador para verificar las vueltas que lleva
			fmt.Printf("\nIterador = %d\n", globalCounter)
			globalCounter++
			fmt.Printf("Fumador con [%s] está fumando, dejenlo.\n", ingredientNames[has])

			// Quita los ingredientes de la mesa
			onTable[(has+1)%numSmokers] = false
			onTable[(has+2)%numSmokers] = false

			// Señalar al agente que termine y ponga nuevos ingredientes
			agentChannel <- struct{}{}
		}
		mutex.Unlock()
	}
}

func main() {
	fmt.Printf("\nEmpieza el codigo...\n\n")
	// Inicializador de rand, para los rand usado en la función de agent
	rand.Seed(time.Now().UnixNano())

	//		El propósito de este código es inicializar cada canal en el array ingredientChannels con un canal buffered 
	// de tamaño 1. Esto permite a cada canal ingredientChannels[i] almacenar una señal (un valor de tipo struct{}) 
	// antes de que un receptor la reciba, lo que es útil para sincronización en concurrencia.
	for i := range ingredientChannels {
		ingredientChannels[i] = make(chan struct{}, 1)
	}

	//		Cuando se usa wg.Add(numSmokers), se está incrementando el contador interno del WaitGroup (wg) en la cantidad 
	// de fumadores que hay en el programa. Esto indica que hay varias goroutines que el programa debe esperar a que 
	// terminen antes de continuar.
	wg.Add(numSmokers)

	for i := 0; i < numSmokers; i++ {
		go smoker(i, Ingrediente(i))
	}

	go agent()

	agentChannel <- struct{}{}

	wg.Wait()
	fmt.Println("Proceso completado")
}