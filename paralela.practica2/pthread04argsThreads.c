#include <stdio.h>
#include <pthread.h>

#define TOTAL_THREADS 16
pthread_mutex_t mutex;

struct arguments{
    int a;
    int b;
};

void *sum(void *arg){


    //Bloqueo para que cree el hilo y haga la operación en calma
    pthread_mutex_lock(&mutex);

    struct arguments *args = (struct arguments *)arg;
    int result = args->a + args->b;
    printf("Result: %d\n", result);

    //Desbloque para que siga con otro hilo
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);

}

int main(void){

    //Declara array de identificadores de hilo
    pthread_t threads[TOTAL_THREADS];

    //Array creado con los structs y con distintos argumentos
    struct arguments args[TOTAL_THREADS] = {
        {1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}, {11, 12}, {13, 14}, {15, 16},
        {17, 18}, {19, 20}, {21, 22}, {23, 24}, {25, 26}, {27, 28}, {29, 30}, {31, 32}
    };

    //Inicialización de Mutex para evitar errores de sincronización
    pthread_mutex_init(&mutex, NULL);

    //Implementacion y creación de hilos
    for (int i = 0; i < TOTAL_THREADS; i++) { //Por cada iteración se usa un identificador de hilo
    

        if (pthread_create(&threads[i], NULL, sum, &args[i]) != 0) {
            perror("Error creating thread\n");
            return 1;
        }

    }

    //Esperar a que los hilos terminen la ejecución para cerrarlos y terminar el programa
    for (int i = 0; i < TOTAL_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    //Destruir el mutex
    pthread_mutex_destroy(&mutex);

    return 0;

}