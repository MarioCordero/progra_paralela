#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <stdint.h>

#define MAX_THREADS 50000

int total_threads;
int points_inside_circle = 0;
int total_points;

void *throw_darts(void *arg){

    int childID = (uintptr_t)arg;
    int points_per_thread = total_points / total_threads;
    unsigned int seed = time(NULL) * (childID + 1);
    for (int i = 0; i < points_per_thread; i++)
    {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;
        if (sqrt(x * x + y * y) <= 1)
        {
            points_inside_circle++;
        }
    }
    return NULL;
}

int main(int argc, char *argv[]){

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

    // RELOJ
    struct timespec before;
    clock_gettime(CLOCK_MONOTONIC, &before);

    // Acá deberán introducir el paralelismo
    throw_darts((void *)1);

    double pi = 4.0 * points_inside_circle / total_points;

    // RELOJ
    // Fuente: https://www.youtube.com/watch?v=1KQqpiXxvWQ
    struct timespec after;
    clock_gettime(CLOCK_MONOTONIC, &after);
    long secs = after.tv_sec-before.tv_sec;
    uint64_t nanosecs = ((after.tv_sec*1000000000) + after.tv_nsec)-((before.tv_sec*1000000000) + before.tv_nsec);
    printf("\n\n\t---------------TIEMPO DE EJECUCION------------------");
    printf("\n\t%ld sec, %ld nanosecs. \n", secs, nanosecs);

    printf("\n\tValor de pi: %f\n", pi);

    return 0;
}