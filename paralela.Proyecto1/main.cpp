#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "channel.h"
#include <pthread.h>

using namespace std;

// Mutex para sincronizar la salida en la consola
pthread_mutex_t mtx;

// Definir el total de hilos a usar
#define TOTAL_THREADS 5

// Variable de condición para notificar a los consumidores
pthread_cond_t cond_var;

// Se crea el struct para pasar el argumento a los hilos, el cual es principalmente la cola
struct threadData {
    //Ya no se usa la cola directamente, sino la clase Chanel (El canal)
    Channel<string> *lineas;
};


// ---------------------------------------METODOS-------------------------------------------//

// Metodo de imprimir
void *printQueue(void *threadDataPointer){ // El parametro de esta funcion es un puntero generico, un puntero generico es un puntero que puede apuntar a cualquier tipo de dato

    // Recibir correctamente el struct y desreferenciarlo
    struct threadData *data = (struct threadData *)threadDataPointer;
    //Definir un canal de stringsm ya no es una cola
    Channel<string> *lineas = data->lineas;


    while (true) {

        //Uso de "auto" porque en receiveChannel() devuelve un optional<T>
        auto valorGenerico = lineas->receiveChannel();
        string linea = *valorGenerico;
        cout << "Procesando línea: " << linea << endl;
    }

    pthread_exit(NULL);

}

// Metodo productor
void productor(Channel<string> *canalStrings) {
    string linea;
    cerr << "\n\tIngrese el texto. Ctrl+D para finalizar.\n" << endl;
    while (getline(cin, linea)) {
        canalStrings->sendChannel(linea);
    }
}


// -----------------------------------------MAIN--------------------------------------------//
int main() {

    // Definir cuantos hilos se van a usar, una constante o una variable que define cuántos hilos se van a crear
    pthread_t threads[TOTAL_THREADS];

    // Inicialización de Mutex para evitar errores de sincronización
    pthread_mutex_init(&mtx, NULL);

    // Inicializar el canal
    Channel<string> canalStrings;

    // Inicializar el struct
    threadData info;
    // Asignar el canal al struct para poder pasarlo a los hilos
    info.lineas = &canalStrings;


    for (int i = 0; i < TOTAL_THREADS; i++) { //Por cada iteración se usa un identificador de hilo

        if (pthread_create(&threads[i], NULL, printQueue, &info) != 0) { //Se esta enviando como argumento un struct que adentro tiene la direccion de memoria de la cola
            perror("Error creating thread\n");
            return 1;
        }

    }

    // Se ejecuta el metodo productor, con el canal para lo carguen con los strings
    productor(&canalStrings);

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