#include <iostream>
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <pthread.h>

using namespace std;

// Mutex para sincronizar la salida en la consola
pthread_mutex_t mtx;

// Definir el total de hilos a usar
#define TOTAL_THREADS 5

// Variable de condición para notificar a los consumidores
pthread_cond_t cond_var;

// Cola para almacenar las líneas leídas por entrada estandar
queue<string> lineasSTD;

// Se crea el struct para pasar el argumento a los hilos, el cual es principalmente la cola
struct threadData {
    queue<string> *lineas;
    unordered_map<string, int> *wordCount;
};


// ---------------------------------------METODOS-------------------------------------------//

// Metodo de imprimir
void *printQueue(void *threadDataPointer){ // El parametro de esta funcion es un puntero generico, un puntero generico es un puntero que puede apuntar a cualquier tipo de dato

    // Recibir correctamente el struct y desreferenciarlo
    struct threadData *data = (struct threadData *)threadDataPointer;
    // Inicializar una cola con la direccion de memoria de la cola usada
    queue<string> *lineas = data->lineas;
    unordered_map<string, int> *wordCount = data->wordCount;


    while (true) {
        // Lock
        pthread_mutex_lock(&mtx);

        // Esperar hasta que haya datos en la cola
        while (lineas->empty()) {
            pthread_cond_wait(&cond_var, &mtx);
        }

        // Procesar una línea de la cola
        if (!lineas->empty()) {
            string line = lineas->front();
            lineas->pop();
            pthread_mutex_unlock(&mtx);
            
            // Procesar la línea fuera del bloqueo para permitir más concurrencia
            cout << "Procesando línea: " << line << endl;

            // Separar las palabras en la línea y actualizar el contador en la tabla hash local
            istringstream iss(line);
            string word;
            while (iss >> word) {
                (*wordCount)[word]++;
            }

        } else {
            pthread_mutex_unlock(&mtx);
        }
    }
    pthread_exit(NULL);
}

// Metodo productor
void productor() {

    string linea;
    cerr << "\n\tIngrese el texto. Ctrl+D para finalizar.\n" << endl;
    while (getline(cin, linea)) {
        // Lock
        pthread_mutex_lock(&mtx);

        // Encolar la línea leída por entrada estándar
        lineasSTD.push(linea);

        // Notificar a los consumidores que hay datos disponibles
        pthread_cond_signal(&cond_var);

        // Unlock
        pthread_mutex_unlock(&mtx);
    }
}


// -----------------------------------------MAIN--------------------------------------------//
int main() {

    // Definir cuantos hilos se van a usar, una constante o una variable que define cuántos hilos se van a crear
    pthread_t threads[TOTAL_THREADS];

    // Inicialización de Mutex para evitar errores de sincronización
    pthread_mutex_init(&mtx, NULL);

    // Inicializar las estructuras con la dirección de memoria de la cola y sus hash tables
    threadData info[TOTAL_THREADS];
    unordered_map<string, int> wordCounts[TOTAL_THREADS];

    // Inicializar el struct con la direccion de memoria de la cola
    //threadData info;

    // En este struct creado, asignarle el atributo "lineas" con la direccion de memoria de la cola
    //info.lineas = &lineasSTD;

    for (int i = 0; i < TOTAL_THREADS; i++) { //Por cada iteración se usa un identificador de hilo
        
        info[i].lineas = &lineasSTD;
        info[i].wordCount = &wordCounts[i];
        
        // Se está enviando como argumento un struct que adentro tiene la dirección de memoria de la cola y de la tabla hash
        if (pthread_create(&threads[i], NULL, printQueue, &info[i]) != 0) { 
            perror("Error creating thread\n");
            return 1;
        }

    }

    // Se ejecuta el metodo productor
    productor();

    // Esperar a que los hilos terminen la ejecución para cerrarlos y terminar el programa
    for (int i = 0; i < TOTAL_THREADS; ++i) {
        pthread_cancel(threads[i]);
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond_var);

    // Mostrar el contenido de las tablas hash de cada hilo
    for (int i = 0; i < TOTAL_THREADS; ++i) {
        cout << "Contenido de la tabla hash del hilo " << i << ":\n";
        for (const auto& entry : wordCounts[i]) {
            cout << entry.first << ": " << entry.second << endl;
        }
    }

    return 0;
}