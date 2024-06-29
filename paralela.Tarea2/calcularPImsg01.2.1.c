#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <stdint.h>
#include <time.h>

#define MAX_THREADS 5000

pthread_mutex_t queue_mutex;
pthread_cond_t queue_cond;

int total_threads;
int points_inside_circle = 0;
int total_points;

// Estructura de nodo para la cola
struct node {
    int points;
    struct node *next;
};

// Cola para mensajes
struct queue {
    struct node *front;
    struct node *rear;
} message_queue;

// Inicializar la cola
void init_queue(struct queue *q) {
    q->front = q->rear = NULL;
}

// Función para insertar en la cola (push)
void push(struct queue *q, int points) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->points = points;
    temp->next = NULL;
    pthread_mutex_lock(&queue_mutex);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
    pthread_cond_signal(&queue_cond);
    pthread_mutex_unlock(&queue_mutex);
}

// Función para eliminar de la cola (pop)
int pop(struct queue *q) {
    pthread_mutex_lock(&queue_mutex);
    while (q->front == NULL) {
        pthread_cond_wait(&queue_cond, &queue_mutex);
    }
    struct node *temp = q->front;
    int points = temp->points;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    pthread_mutex_unlock(&queue_mutex);
    return points;
}

void *throw_darts(void *arg) {
    int local_points = 0;
    int childID = (uintptr_t)arg;
    int points_per_thread = total_points / total_threads;
    unsigned int seed = time(NULL) * (childID + 1);

    for (int i = 0; i < points_per_thread; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;
        if (sqrt(x * x + y * y) <= 1) {
            local_points++;
        }
    }

    // Enviar puntos al hilo principal
    push(&message_queue, local_points);
    return NULL;
}

int main(int argc, char *argv[]) {
    
    total_points = atoi(argv[1]);
    total_threads = atoi(argv[2]);

    if (total_threads > MAX_THREADS) {
        printf("El número de hilos no puede ser mayor a %d\n", MAX_THREADS);
        return 1;
    }

    if (total_points % total_threads != 0) {
        printf("El número de puntos debe ser divisible entre el número de hilos\n");
        return 1;
    }

    // RELOJ
    struct timespec before;
    clock_gettime(CLOCK_MONOTONIC, &before);

    // Inicializar mutex y condición
    pthread_mutex_init(&queue_mutex, NULL);
    pthread_cond_init(&queue_cond, NULL);

    // Inicializar cola
    init_queue(&message_queue);

    pthread_t threads[MAX_THREADS];

    // Implementación y creación de los hilos
    for (int i = 0; i < total_threads; i++) {
        if (pthread_create(&threads[i], NULL, throw_darts, (void *)(uintptr_t)i) != 0) {
            perror("Error creating thread\n");
            return 1;
        }
    }

    // Esperar a que los hilos terminen la ejecución para que no haya problemas
    for (int i = 0; i < total_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    points_inside_circle = 0;

    // Obtener todos los mensajes
    for (int i = 0; i < total_threads; i++) {
        points_inside_circle += pop(&message_queue);
    }
    double pi = 4.0 * points_inside_circle / total_points;

    // RELOJ
    // Fuente: https://www.youtube.com/watch?v=1KQqpiXxvWQ
    struct timespec after;
    clock_gettime(CLOCK_MONOTONIC, &after);
    long secs = after.tv_sec-before.tv_sec;
    uint64_t nanosecs = ((after.tv_sec*1000000000) + after.tv_nsec)-((before.tv_sec*1000000000) + before.tv_nsec);
    printf("\n\n\t---------------TIEMPO DE EJECUCION------------------");
    printf("\n\t%ld sec, %ld nanosecs. \n", secs, nanosecs);

    printf("\n\tValor de pi: %f\n\n", pi);

    // Destruir el mutex y la condición
    pthread_mutex_destroy(&queue_mutex);
    pthread_cond_destroy(&queue_cond);

    return 0;
}