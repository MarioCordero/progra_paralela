#include <stdio.h>
#include <pthread.h>

#define TOTAL_THREADS 16
int global = 0;

void *increment(void *arg){

    for (int i = 0; i < 1000; i++){

        global++;
        
    }
    pthread_exit(NULL);

}

int main(void){

    pthread_t threads[TOTAL_THREADS];
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
    return 0;

}