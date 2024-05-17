#include <iostream>
#include <string>
#include <queue>
#include <thread>
#include <mutex>

using namespace std;

// Mutex para sincronizar la salida en la consola
pthread_mutex_t mtx;

// Definir el total de hilos a usar
#define TOTAL_THREADS 5

// Se crea el struct para pasar el argumento a los hilos, el cual es principalmente la cola
struct threadData {
    queue<string> *lineas;
};


// ---------------------------------------METODOS-------------------------------------------//
void *printQueue(void *threadDataPointer){ // El parametro de esta funcion es un puntero generico, un puntero generico es un puntero que puede apuntar a cualquier tipo de dato

    // Recibir correctamente el struct y desreferenciarlo
    struct threadData *data = (struct threadData *)threadDataPointer;
    // Inicializar una cola con la direccion de memoria de la cola usada
    queue<string> *lineas = data->lineas;

    //Lock
    pthread_mutex_lock(&mtx);

    if(!lineas->empty()) {
        cout << lineas->front() << endl;
        lineas->pop();
    }

    //Unlock
    pthread_mutex_unlock(&mtx);
    
    pthread_exit(NULL);

}


// -----------------------------------------MAIN--------------------------------------------//
int main() {

    // Definir cuantos hilos se van a usar, una constante o una variable que define cuántos hilos se van a crear
    pthread_t threads[TOTAL_THREADS];

    // Inicialización de Mutex para evitar errores de sincronización
    pthread_mutex_init(&mtx, NULL);

    // Cola para almacenar las líneas leídas por entrada estandar
    queue<string> lineasSTD;

    // Declarar la linea donde se va a almacenar lo leido por entrada estandar
    string linea;
    int contador = 0;

    cout << "\n\tIngrese el texto. Ctrl+D para finalizar.\n" << endl;
    while (getline(cin, linea)) {

        // Encolar la linea leida por entrada estandar
        lineasSTD.push(linea);
        // Aumentar el contador
        contador++;

        if(contador == 5){
            
            cout << "\nLimite de lineas alcanzado, imprimiendo...\n" << endl;
            // Inicializar el struct con la direccion de memoria de la cola
            threadData info;
            // En este struct creado, asignarle el atributo "lineas" con la direccion de memoria de la cola
            info.lineas = &lineasSTD;

            for (int i = 0; i < TOTAL_THREADS; i++) { //Por cada iteración se usa un identificador de hilo
            
                if (pthread_create(&threads[i], NULL, printQueue, &info) != 0) { //Se esta enviando como argumento un struct que adentro tiene la direccion de memoria de la cola
                    perror("Error creating thread\n");
                    return 1;
                }

            }

            //Esperar a que los hilos terminen la ejecución para cerrarlos y terminar el programa
            for (int i = 0; i < TOTAL_THREADS; i++) {
                pthread_join(threads[i], NULL);
            }

            //Reiniciar contador
            contador = 0;
        }

    }
    
    // Esperar a que todos los hilos terminen
    // pthread_mutex_lock(&mtx);
    // pthread_mutex_unlock(&mtx);

    pthread_mutex_destroy(&mtx);
    return 0;
}