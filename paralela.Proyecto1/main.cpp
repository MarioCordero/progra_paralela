#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "channel.h"
#include <pthread.h>
#include <unordered_map>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

// Mutex para sincronizar la salida en la consola
pthread_mutex_t mtx;

// Definir el total de hilos a usar
#define TOTAL_THREADS 5

// Variable de condición para notificar a los consumidores
pthread_cond_t cond_var;

unordered_map<string, int> global;

// Se crea el struct para pasar el argumento a los hilos, el cual es principalmente la cola
struct threadData {
    //Ya no se usa la cola directamente, sino la clase Chanel (El canal)
    Channel<string> *lineas;
    unordered_map<string, int> *wordCount;
};

// Función para extraer las claves de la tabla hash en un vector
vector<string> obtenerClaves(const unordered_map<string, int>& wordCount) {
    vector<string> claves;
    for (const auto& par : wordCount) {
        claves.push_back(par.first);
    }
    return claves;
}


// Combinar dos subarreglos ordenados en uno solo
	void merge(vector<string>& A, int izquierda, int divido, int derecha)
	{
		// Calcular los tamaños de los dos subarreglos a fusionar
		int tamano1 = divido - izquierda + 1;
		int tamano2 = derecha - divido;
		// Arreglos temporales para almacenar los elementos de los subarreglos
        vector<string> arreglo1(tamano1), arreglo2(tamano2);

		// Se copian los elementos de los subarreglos originales en los arreglos temporales
		for (int i = 0; i < tamano1; i++)
		{
			arreglo1[i] = A[izquierda + i];
		} // Fin for

		for (int j = 0; j < tamano2; j++)
		{
			arreglo2[j] = A[divido + 1 + j];
		} // Fin for

		// Fusionar los dos arreglos temporales en el arreglo original
		int i = 0;
		int j = 0;
		int k = izquierda;

		while (i < tamano1 && j < tamano2)
		{
			if (arreglo1[i] <= arreglo2[j])
			{
				A[k] = arreglo1[i];
				i++;
			}
			else
			{
				A[k] = arreglo2[j];
				j++;
			} // Fin if
			k++;
		} // Fin while

		// Copiar los elementos restantes del primer subarreglo, si hay
		while (i < tamano1)
		{
			A[k] = arreglo1[i];
			i++;
			k++;
		} // Fin while

		// Se copian los elementos restantes del segundo subarreglo, si hay
		while (j < tamano2)
		{
			A[k] = arreglo2[j];
			j++;
			k++;
		} // Fin while
	} // Fin merge

/* Divide recursivamente el arreglo en subarreglos más pequeños, hasta que cada subarreglo
	tenga uno o ningún elemento. Luego, combina los subarreglos ordenados de manera consecutiva
	utilizando la función merge */
	void mergeRecursivo(vector<string>& A, int inicio, int final)
	{
		// Verifica si el índice de inicio es menor que el índice final, indicando que hay elementos en el subarreglo a ordenar
		if (inicio < final)
		{
			// Se calcula el punto medio del subarreglo
			int divido = inicio + (final - inicio) / 2;
			// Ordenar la primera mitad del subarreglo
			mergeRecursivo(A, inicio, divido);
			// Ordenar la segunda mitad del subarreglo
			mergeRecursivo(A, divido + 1, final);
			// Merge para combinar las dos mitades ordenadas del subarreglo
			merge(A, inicio, divido, final);
		} // Fin if
	} // Fin mergeRecursivo

	

    // Algoritmo de ordenamiento Merge Sort
	void mergesort(vector<string>& A)
	{
        mergeRecursivo(A, 0, A.size() - 1);
	} // Fin mergesort
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mergeHahs(unordered_map<string, int>& global, unordered_map<string, int> wordCount) {

      // Agregar elementos de la tabla local al global
    for (const auto& pair : wordCount) {
        //global[pair.first] = pair.second;

        /////// 
        if (global.find(pair.first) != global.end()) {
            // Si el elemento está en la primera tabla, incrementar el contador
           // cout << "adios" << endl;
            global[pair.first]++;
        } else {
           // cout << "holaa" << endl;
            // Si no está en la primera tabla, agregar el elemento
            global[pair.first] = pair.second;
        }
    }
}

// ---------------------------------------METODOS-------------------------------------------//

// Metodo de imprimir
// El parametro de esta funcion es un puntero generico, un puntero generico es un puntero que puede apuntar a cualquier tipo de dato
void *printQueue(void *threadDataPointer){ 

    // Recibir correctamente el struct y desreferenciarlo
    struct threadData *data = (struct threadData *)threadDataPointer;

    // Definir un canal de stringsm ya no es una cola
    Channel<string> *lineas = data->lineas;
    unordered_map<string, int> *wordCount = data->wordCount;

    while (true) {

        //Uso de "auto" porque en receiveChannel() devuelve un optional<T>
        auto valorGenerico = lineas->receiveChannel();
        string linea = *valorGenerico;
      //  cout << "\n\nProcesando línea: " << linea << endl;
        
        istringstream iss(linea);
        string word;

        while (iss >> word) {
            (*wordCount)[word]++;
        } // End while

    } // End while
    pthread_exit(NULL);
} // End printQueue

// Metodo productor
void productor(Channel<string> *canalStrings) {
    string linea;
    cerr << "\n\tIngrese el texto. Ctrl+D para finalizar.\n" << endl;

    while (getline(cin, linea)) {
        transform(linea.begin(), linea.end(), linea.begin(), ::tolower);
        canalStrings->sendChannel(linea);
    } // End while
} // End productor

// -----------------------------------------MAIN--------------------------------------------//
int main() {

    // Definir cuantos hilos se van a usar, una constante o una variable que define cuántos hilos se van a crear
    pthread_t threads[TOTAL_THREADS];

    // Inicialización de Mutex para evitar errores de sincronización
    pthread_mutex_init(&mtx, NULL);

    // Inicializar el canal
    Channel<string> canalStrings;

    threadData info[TOTAL_THREADS];
    unordered_map<string, int> wordCounts[TOTAL_THREADS];

    for (int i = 0; i < TOTAL_THREADS; i++) {
        info[i].lineas = &canalStrings;
        info[i].wordCount = &wordCounts[i];

        if (pthread_create(&threads[i], NULL, printQueue, &info[i]) != 0) {
            perror("Error creating thread\n");
            return 1;
        } // End if
    } // End for

    // Se ejecuta el metodo productor, con el canal para lo carguen con los strings
    productor(&canalStrings);

    cout << endl;
     for (int i = 0; i < TOTAL_THREADS; ++i) {
        cout << "\nContenido de la tabla hash del hilo " << i << ":\n";
        for (const auto& entry : wordCounts[i]) {
            cout << entry.first << ": " << entry.second << endl;
            // la pasamos al hash global
           // pthread_mutex_lock(&mtx);
           // pthread_mutex_unlock(&mtx);
        }
        mergeHahs(global, wordCounts[i]);
    }

    cout << endl << "Hash table global:\n" << endl;
    for (const auto& pair : global) {
        cout << pair.first << ": " << pair.second << endl;
    }

    vector<string> claves = obtenerClaves(global);
    // Ordenar las claves
    mergesort(claves);
    // Mostrar las claves ordenadas con sus frecuencias
    cout << "\n\nPalabras ordenadas alfabéticamente:\n";
    for (const string& clave : claves) {
        cout << clave << ": " << global[clave] << "\n";
    }

    // Esperar a que los hilos terminen la ejecución para cerrarlos y terminar el programa
    for (int i = 0; i < TOTAL_THREADS; ++i) {
        //Quitar este cancel
        pthread_cancel(threads[i]);
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond_var);
    return 0;
}