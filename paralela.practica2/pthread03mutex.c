#include <stdio.h>
#include <pthread.h>

#define TOTAL_THREADS 16
int global = 0;
pthread_mutex_t mutex;

void *increment(void *arg){

    for (int i = 0; i < 1000; i++){
        
        printf("Thread %ld\n", pthread_self());

        // Seccion critica
        pthread_mutex_lock(&mutex);
        global++;
        pthread_mutex_unlock(&mutex);
        
    }
    pthread_exit(NULL);

}

int main(void){

    pthread_t threads[TOTAL_THREADS];

    // Iniciar el mutex
    pthread_mutex_init(&mutex, NULL);

    printf("Global before: %d\n", global);
    
    for (int i = 0; i < TOTAL_THREADS; i++){

        if (pthread_create(&threads[i], NULL, increment, NULL) != 0){

            perror("Error creating thread\n");
            return 1;
        }
    }

    for (int i = 0; i < TOTAL_THREADS; i++){

        pthread_join(threads[i], NULL);

    }

    printf("Global after: %d\n", global);

    // Destruir el mutex
    pthread_mutex_destroy(&mutex);

    return 0;

}