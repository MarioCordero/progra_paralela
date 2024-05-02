#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>

//Includes
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

#define MAX_THREADS 5000
// pthread_mutex_t mutex;

int total_threads;
int points_inside_circle = 0;
int total_points;

// CREAR UN NODO PARA ENCOLAR/DESENCOLAR CON EL PASO DE MENSAJES
struct msg_buffer {

    int points;

} message;

void *throw_darts(void *arg){

    int *pipefds = (int *)arg; // CASTEO A int* PARA OBTENER LA PIPE

    int local_points = 0;
    int childID = (uintptr_t)arg;
    int points_per_thread = total_points / total_threads;
    unsigned int seed = time(NULL) * (childID + 1);

    for (int i = 0; i < points_per_thread; i++){

        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;
        if (sqrt(x * x + y * y) <= 1){

            local_points++;

        }
    }

    // USAR EL PIPE PARA ENVIAR LOS MENSAJES
    // ABRIR FIFO EN MODO ESCRITURA
    close(pipefds[0]); // CERRAR LECTURA
    write(pipefds[1], &local_points, sizeof(local_points)); // ESCRITURA
    close(pipefds[1]); // CERRAR ESCRITURA

    return NULL;
}



int main(int argc, char *argv[]){

    // RELOJ
    struct timespec before;
    clock_gettime(CLOCK_MONOTONIC, &before);

    // DECLARA ARRAY DE INDENTIFICADORES DE HILO
    pthread_t threads[MAX_THREADS];

    if (argc != 3){

        printf("\n");
		printf("%s \n Error, esto se usa: make ARGS= \" <total_points> <total_threads> \"\n", argv[0]);
		printf("\n");
        return 1;

    }

    total_points = atoi(argv[1]);
    total_threads = atoi(argv[2]);

    if (total_threads > MAX_THREADS){

        printf("El número de hilos no puede ser mayor a %d\n", MAX_THREADS);
        return 1;

    }

    if (total_points % total_threads != 0){

        printf("El número de puntos debe ser divisible entre el número de hilos\n");
        return 1;

    }

    int pipefds[2];
    // Crear un pipe
    if (pipe(pipefds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // IMPLEMENTACIÓN Y CREACIÓN DE LOS HILOS
    for (int i = 0; i < total_threads; i++) { // POR CADA ITERACIÓN SE USA UN ID DE HILO

        if (pthread_create(&threads[i], NULL, throw_darts, (void *)&pipefds) != 0) {
            perror("Error creating thread\n");
            return 1;
        }

    }

    // ESPERAR A QUE LOS HILOS TERMINEN LA EJECUCIÓN PARA QUE NO HAYA PROBLEMAS
    for (int i = 0; i < total_threads; i++) {
        pthread_join(threads[i], NULL);
    }


    points_inside_circle = 0;
    // VACIAR LA PIPE Y OBTENER LOS VALORES

    // double pi = 4.0 * points_inside_circle / total_points;

    // printf("\n\nValor de pi: %f\n\n", pi);

    // RELOJ
    // Fuente: https://www.youtube.com/watch?v=1KQqpiXxvWQ
    struct timespec after;
    clock_gettime(CLOCK_MONOTONIC, &after);
    long secs = after.tv_sec-before.tv_sec;
    uint64_t nanosecs = ((after.tv_sec*1000000000) + after.tv_nsec)-((before.tv_sec*1000000000) + before.tv_nsec);
    printf("%ld sec, %ld nanosecs. \n\n", secs, nanosecs);

    return 0;
}