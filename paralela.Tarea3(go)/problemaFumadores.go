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
type Ingrediente int

// Declaración de constantes
const (
	tabaco 		Ingrediente = 0
	papel   	Ingrediente = 1
	fosforos 	Ingrediente = 2
)

// Nombres de los ingredientes para imprimir, esta sintaxis se usa para definir que es una lista de cadenas
var ingredientNames = []string{
	"Tabaco", 
	"Papel", 
	"Fósforos"}

// Canales para los ingredientes, se usa el numero definido anteriormente y se crea un array de canales
var ingredientChannels [numSmokers]chan struct{}
//		struct{} indica que el tipo de datos que el canal transporta es una estructura vacía. Las estructuras vacías 
// (struct{}) en Go no ocupan espacio, lo que las hace útiles para señales y sincronización, donde el valor en sí no 
// importa, solo el hecho de que se ha enviado algo a través del canal.

// Canal para el agente
//		make es una función integrada en Go que se utiliza para crear canales, slices y mapas.
// chan struct{} indica que estamos creando un canal que transportará valores del tipo struct{}.
var agentChannel = make(
	chan struct{})

// WaitGroup para esperar a que todos los fumadores terminen
// 		Este es el tipo de la variable. sync.WaitGroup es una estructura 
// proporcionada por el paquete sync de Go que permite esperar a que un 
// conjunto de goroutines terminen su ejecución.
var wg sync.WaitGroup

// Mutex para la sincronización
var mutex sync.Mutex

// Estado de los ingredientes en la mesa, este array se usará para saber que ingredientes hay actualmente en el array
var onTable = [numSmokers]bool{false, false, false}

// Función del agente
func agent() {
	// Se una un for sin condicion porque con el "<-agentChannel" se esta esperando señal
	for {
		// Esperar señal para poner ingredientes
		<-agentChannel

		// Seleccionar dos ingredientes aleatorios
		mutex.Lock()
		ingredient1 := rand.Intn(numSmokers)
		ingredient2 := (ingredient1 + rand.Intn(numSmokers-1) + 1) % numSmokers

		// Asegurar que los dos ingredientes sean diferentes
		if ingredient1 == ingredient2 {
			ingredient2 = (ingredient2 + 1) % numSmokers
		}

		// Actualizar el estado de los ingredientes en la mesa, ahora están en la mesa
		onTable[ingredient1] = true
		onTable[ingredient2] = true

		fmt.Printf("El agente pone [%s] y [%s] en la mesa.\n", ingredientNames[ingredient1], ingredientNames[ingredient2])

		// Señalar a los fumadores que los ingredientes están en la mesa

		// 		<- struct{}{} es la sintaxis para enviar una señal a un canal en Go. La estructura vacía struct{} se usa comúnmente 
		// como un tipo de dato para los canales que no necesitan transportar ningún dato, sino simplemente señalar un evento.
		ingredientChannels[ingredient1] <- struct{}{}
		ingredientChannels[ingredient2] <- struct{}{}
		mutex.Unlock()
	}
}

// Función del fumador
func smoker(id int, has Ingrediente) {
	// 		defer wg.Done() se utiliza para indicar al WaitGroup wg que esta goroutine ha terminado después de que la función smoker retorne. 
	// Esto se usa para coordinar la espera de todas las goroutines de los fumadores en la función main.
	defer wg.Done()
	for {
		// Esperar a que los ingredientes estén en la mesa
		<-ingredientChannels[(has+1)%numSmokers]
		<-ingredientChannels[(has+2)%numSmokers]

		mutex.Lock()
		// Verificar si los ingredientes que necesita están en la mesa
		if onTable[(has+1)%numSmokers] && onTable[(has+2)%numSmokers] {
			// Fumar (simulación con sleep)
			fmt.Printf("Fumador con [%s] está fumando, dejenlo.\n", ingredientNames[has])
			time.Sleep(time.Second)

			// Limpiar la mesa
			onTable[(has+1)%numSmokers] = false
			onTable[(has+2)%numSmokers] = false

			// Señalar al agente que termine y ponga nuevos ingredientes
			agentChannel <- struct{}{}
		}
		mutex.Unlock()
	}
}

func main() {
	rand.Seed(time.Now().UnixNano())

	// Inicializar los canales
	for i := range ingredientChannels {
		ingredientChannels[i] = make(chan struct{}, 1) // Hacer los canales con buffer de tamaño 1
	}

	// Añadir fumadores al WaitGroup
	wg.Add(numSmokers)

	// Iniciar las goroutines de los fumadores
	for i := 0; i < numSmokers; i++ {
		go smoker(i, Ingrediente(i))
	}

	// Iniciar la goroutine del agente
	go agent()

	// Iniciar el proceso con una señal al agente
	agentChannel <- struct{}{}

	// Esperar a que los fumadores terminen (nunca sucede en esta simulación)
	wg.Wait()
}