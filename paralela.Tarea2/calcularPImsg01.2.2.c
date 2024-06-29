#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <stdint.h>
#include <time.h>

//Includes
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_THREADS 5000
pthread_mutex_t mutex;

int total_threads;
int points_inside_circle = 0;
int total_points;

// CREAR UN NODO PARA ENCOLAR/DESENCOLAR CON EL PASO DE MENSAJES
struct msg_buffer {

    int points;

} message;

void *throw_darts(void *arg){
    int local_points = 0;

    // INICIAMOS LA KEY DE LA COLA Y EL MSG ID
    key_t key;
    int msgid;

    // GENERAMOS UNA CLAVE ÚNICA PARA LA COLA
    key = ftok("queuefile", 65);

    // CONECTAMOS A LA COLA DE MENSAJES CREADA Y OBTENEMOS SU ID
    msgid = msgget(key, 0666 | IPC_CREAT);

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

    // CREAR EL STRUCT PARA ALMACENAR LOS DATOS
    struct msg_buffer msg;

    // CREAMOS EL MENSAJE CON LOS PUNTOS QUE GENERA CADA HILO
    msg.points = local_points;

    // BLOQUEAR EL MUTEX
    pthread_mutex_lock(&mutex);

        // ENVIAR EL NODO, MENSAJE
        msgsnd(msgid, &msg, sizeof(message), 0);

        // MOSTRAR EL PUNTO ENVIADO
        printf("\nMensaje enviado: %i", msg.points);
        
    // DESBLOQUEAR EL MUTEX
    pthread_mutex_unlock(&mutex);

    return NULL;
}



int main(int argc, char *argv[]){


    // DECLARA ARRAY DE INDENTIFICADORES DE HILO
    pthread_t threads[MAX_THREADS];

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

    // INICIAMOS LA KEY DE LA COLA Y EL MSG ID
    key_t key;
    int msgid;

    // GENERAMOS LA CLAVE ÚNICA PARA LA COLA
    key = ftok("queuefile", 65);

    // CREAMOS LA COLA Y OBTENEMOS SU ID
    msgid = msgget(key, 0666 | IPC_CREAT);

    //Inicialización de Mutex para evitar errores de sincronización
    pthread_mutex_init(&mutex, NULL);

    // IMPLEMENTACIÓN Y CREACIÓN DE LOS HILOS
    for (int i = 0; i < total_threads; i++) { // POR CADA ITERACIÓN SE USA UN ID DE HILO

        if (pthread_create(&threads[i], NULL, throw_darts, NULL) != 0) {
            perror("Error creating thread\n");
            return 1;
        }

    }

    // ESPERAR A QUE LOS HILOS TERMINEN LA EJECUCIÓN PARA QUE NO HAYA PROBLEMAS
    for (int i = 0; i < total_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    points_inside_circle = 0;

    // OBTENER TODOS LOS MENSAJES
    for (int i = 0; i < total_threads; i++) {

        // RECIBIR EL MENSAJE
        msgrcv(msgid, &message, sizeof(message), 0, 0);

        // SUMA EL CONTADOR DE PUNTOS EN TOTAL
        points_inside_circle += message.points;

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

    // ELIMINAMOS LA COLA
    msgctl(msgid, IPC_RMID, NULL);

    //Destruir el mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}