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

	if (argc != 3) {
		printf("\n");
		printf("%s \n Error, esto se usa: make ARGS= \" <total_points> <total_threads> \"\n", argv[0]);
		printf("\n");
		return 1;
	}

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
	printf(" \nValor de pi: %f\n\n", pi);

	// Destruccion del mutex
	pthread_mutex_destroy(&mutex);

	return 0;
}