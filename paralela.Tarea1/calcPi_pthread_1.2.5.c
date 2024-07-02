#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <stdint.h>

#include <stdatomic.h>

#define MAX_THREADS 50000 //Max amount of threads

// Variables globales
int total_threads;


atomic_int points_inside_circle = 0; // Variable atomica


int total_points;

// Inicializador del mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* throw_darts(void* arg) {
	
	int local_points_counter = 0;

	int childID = (uintptr_t)arg;
	int points_per_thread = total_points / total_threads;
	unsigned int seed = time(NULL) * (childID + 1);
	for (int i = 0; i < points_per_thread; i++) {
	double x = (double)rand_r(&seed) / RAND_MAX;
	double y = (double)rand_r(&seed) / RAND_MAX;

		if (sqrt(x * x + y * y) <= 1) {
			local_points_counter++;
		}
	}

	// Retornar el falso puntero con la cantidad de puntos
    return (void*)(uintptr_t)local_points_counter;

  return NULL;
}

int main(int argc, char* argv[]) {

	// Los numeros que son enviados por argumento
	total_points = atoi(argv[1]);
	total_threads = atoi(argv[2]);

	if (total_threads > MAX_THREADS) {
		printf("El número de hilos no puede ser mayor a %d\n", MAX_THREADS);
		return 1;
	}if (total_points % total_threads != 0) {
		printf("El número de puntos debe ser divisible entre el número de hilos\n");
		return 1;
	}

	// Acá deberán introducir el paralelismo

	// RELOJ
    struct timespec before;
    clock_gettime(CLOCK_MONOTONIC, &before);
	
	pthread_t threads[MAX_THREADS];

	// Creacion de hilos
	for (int i = 0; i < total_threads; ++i) {
		if( pthread_create(&threads[i], NULL, throw_darts, NULL) != 0 ){
			perror("Error creating thread\n");
			return 1;
		}
	}


	// Cierre de hilos
	for (int i = 0; i < total_threads; ++i) {

		void* result;//Falso puntero

        pthread_join(threads[i], &result);
        points_inside_circle += (intptr_t)result;
		
	}

	double pi = 4.0 * points_inside_circle / total_points;

	// RELOJ
    // Fuente: https://www.youtube.com/watch?v=1KQqpiXxvWQ
	struct timespec after;
	clock_gettime(CLOCK_MONOTONIC, &after);
	long secs = after.tv_sec - before.tv_sec;
	uint64_t nanosecs = ((after.tv_sec * 1000000000) + after.tv_nsec) - ((before.tv_sec * 1000000000) + before.tv_nsec);
	uint64_t millisecs = nanosecs / 1000000;  // Convertir nanosegundos a milisegundos
	printf("\n\n\t---------------TIEMPO DE EJECUCION------------------");
	printf("\n\t%ld sec, %ld milisecs, %ld nanosecs. \n", secs, millisecs, nanosecs);

	printf("\n\tValor de pi: %f\n\n", pi);

	// Destruccion del mutex
	pthread_mutex_destroy(&mutex);

	return 0;
}