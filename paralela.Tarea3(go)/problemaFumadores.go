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

// Función del agente
func agent() {
	for {
		<-agentChannel
		fmt.Println("\nAgente recibió señal para poner ingredientes en la mesa.\n")

		ingredient1 := rand.Intn(numSmokers)
		ingredient2 := (ingredient1 + rand.Intn(numSmokers-1) + 1) % numSmokers

		if ingredient1 == ingredient2 {
			ingredient2 = (ingredient2 + 1) % numSmokers
		}

		fmt.Printf("El agente pone [%s] y [%s] en la mesa.\n", ingredientNames[ingredient1], ingredientNames[ingredient2])

		// Aqui enviamos las señales a los canales
		ingredientChannels[ingredient1] <- struct{}{}
		ingredientChannels[ingredient2] <- struct{}{}

		// Ya terminó el agente
		wg.Done()
	}
}

// Función del fumador
func smoker(has Ingrediente) {
	// 		cuando se ejecuta defer wg.Done(), se está indicando que, cuando una goroutine de fumador finalice su trabajo y 
	// esté a punto de retornar, se debe informar al WaitGroup que esa goroutine ha terminado. Esto decrementa el contador 
	// interno del WaitGroup.
	for {

		select{
			// Caso de que me llegue una señal
			case <-ingredientChannels[(has+1)%numSmokers]:

				select{
					// Caso de que me llegue la otra señal
					case <-ingredientChannels[(has+2)%numSmokers]:
						// tengo 2 ingredientes, proceda a fumar
						fmt.Printf("Fumador con [%s] está fumando, dejenlo.\n", ingredientNames[has])
						time.Sleep(time.Second) 

						// Indicarle al agente que puede poner otra vez los elementos en la mesa
						agentChannel <- struct{}{}
					// Fin del caso

					// Caso default
					default:
						ingredientChannels[(has+1)%numSmokers] <- struct {}{}
					// Fin del caso
				}

			// Fin del caso

			// Caso default
			default:
				//No haga nada
			// Fin del caso
		}
	}
}

func main() {
	// Inicializador de rand, para los rand usado en la función de agent
	rand.Seed(time.Now().UnixNano())

	// Crear los canales de cada ingrediente
	for i := range ingredientChannels {
		ingredientChannels[i] = make(chan struct{}, 1)
	}

	// Añadir al wg un entero que indica que hay 1 elemento ejecutandose
	wg.Add(1)

	// Enviando la señal al canal del agente, que puede poner los ingredientes en la mesa
	agentChannel <- struct{}{}
	// Ejecutar el agente
	go agent()

	// Esperar al done que reste el 1 de wg, para verificar que el agente ponga todo sobre la mesa
	wg.Wait()
	
	for i := 0; i < numSmokers; i++ {
		// Añadir al wg un entero que indica que hay 1 elemento ejecutandose
		wg.Add(1)
		// Ejecutar el fumador
		go smoker(Ingrediente(i))
	}

	// Esperar al done que reste el 1 de wg para terminar el programa
	wg.Wait()

	fmt.Println("\n\nProceso completado")
}