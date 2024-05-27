#include <iostream>
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <pthread.h>
#include <sstream>

using namespace std;

// Mutex para sincronizar la salida en la consola
pthread_mutex_t mtx;

// Definir el total de hilos a usar
#define TOTAL_THREADS 5

// Variable de condición para notificar a los consumidores
pthread_cond_t cond_var;

// Cola para almacenar las líneas leídas por entrada estandar
queue<string> lineasSTD;

// Variable para indicar si el productor ha terminado
bool producerDone = false;

// Se crea el struct para pasar el argumento a los hilos, el cual es principalmente la cola
struct threadData {
    queue<string> *lineas;
    unordered_map<string, int> *wordCount;
};

// ---------------------------------------METODOS-------------------------------------------//

// Metodo de imprimir
void *printQueue(void *threadDataPointer){
    struct threadData *data = (struct threadData *)threadDataPointer;
    queue<string> *lineas = data->lineas;
    unordered_map<string, int> *wordCount = data->wordCount;

    while (true) {
        pthread_mutex_lock(&mtx);

        while (lineas->empty() && !producerDone) {
            pthread_cond_wait(&cond_var, &mtx);
        }

        if (lineas->empty() && producerDone) {
            pthread_mutex_unlock(&mtx);
            break;
        }

        string line = lineas->front();
        lineas->pop();
        pthread_mutex_unlock(&mtx);

        pthread_mutex_lock(&mtx);
        cout << "\nProcesando línea: " << line << endl;
        pthread_mutex_unlock(&mtx);

        istringstream iss(line);
        string word;
        while (iss >> word) {
            (*wordCount)[word]++;
        }
    }
    pthread_exit(NULL);
}

// Metodo productor
void productor() {
    string linea;
    cerr << "\n\tIngrese el texto. Ctrl+D para finalizar.\n" << endl;
    while (getline(cin, linea)) {
        pthread_mutex_lock(&mtx);
        lineasSTD.push(linea);
        pthread_cond_signal(&cond_var);
        pthread_mutex_unlock(&mtx);
    }

    pthread_mutex_lock(&mtx);
    producerDone = true;
    pthread_cond_broadcast(&cond_var);
    pthread_mutex_unlock(&mtx);
}

// -----------------------------------------MAIN--------------------------------------------//
int main() {
    pthread_t threads[TOTAL_THREADS];
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&cond_var, NULL);

    threadData info[TOTAL_THREADS];
    unordered_map<string, int> wordCounts[TOTAL_THREADS];

    for (int i = 0; i < TOTAL_THREADS; i++) {
        info[i].lineas = &lineasSTD;
        info[i].wordCount = &wordCounts[i];

        if (pthread_create(&threads[i], NULL, printQueue, &info[i]) != 0) {
            perror("Error creating thread\n");
            return 1;
        }
    }

    productor();

    for (int i = 0; i < TOTAL_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond_var);

    for (int i = 0; i < TOTAL_THREADS; ++i) {
        cout << "Contenido de la tabla hash del hilo " << i << ":\n";
        for (const auto& entry : wordCounts[i]) {
            cout << entry.first << ": " << entry.second << endl;
        }
    }

    return 0;
}
