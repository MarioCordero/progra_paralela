#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <stdint.h>

//Includes
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

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

    printf("\n\nValor de pi: %f\n\n", pi);

    // RELOJ
    // Fuente: https://www.youtube.com/watch?v=1KQqpiXxvWQ
    struct timespec after;
    clock_gettime(CLOCK_MONOTONIC, &after);
    long secs = after.tv_sec-before.tv_sec;
    uint64_t nanosecs = ((after.tv_sec*1000000000) + after.tv_nsec)-((before.tv_sec*1000000000) + before.tv_nsec);
    printf("%ld sec, %ld nanosecs. \n\n", secs, nanosecs);

    // ELIMINAMOS LA COLA
    msgctl(msgid, IPC_RMID, NULL);

    //Destruir el mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}

// // -----------------------------------------------------IGNORAR POR FAVOR SOY UN IDIOTA-------------------------------------------------------//
// // CREAR UN NODO PARA ENCOLAR/DESENCOLAR
// typedef struct Node {

//     int data; // RESULTADO

//     struct Node* next; // PUNTERO AL SIGUIENTE NODO

// } Node;

// // -------------------------------------------------------------------------------------------------------------------------------------//
// // -----------------------------------------------------IMPLEMENTACIÓN DE LA COLA-------------------------------------------------------//
// // -------------------------------------------------------------------------------------------------------------------------------------//

// // CREAR LA ESTRUCTURA DE LA COLA
// typedef struct {

//     Node* first; // CABEZA DE LA COLA

//     Node* last; // COLA DE LA COLA xd

//     // pthread_mutex_t mutex;

// } Queue;

// // INICIALIZAR COLA
// void initializeQueue(Queue* q) {

//     // INICIALIZAR COLA, TODO EN NULO
//     q->first = NULL;
//     q->last = NULL;
//     // pthread_mutex_init(&q->mutex, NULL);

// }

// // ENCOLAR
// void push(Queue* q, int MESSAGE) {

//     Node* newNode = malloc(sizeof(Node)); // CREAR Y RESERVAR MEMORIA PARA EL NUEVO NODO DE LA COLA
//     newNode->data = MESSAGE; // EL NUMERO CALCULADO POR EL HILO
//     newNode->next = NULL;
    
//     // pthread_mutex_lock(&q->mutex);
    
//     if (q->last == NULL) { // SI LA COLA ESTA VACÍA
//         q->first = q->last = newNode;
//     } else { // SI LA COLA NO ESTA VACÍA
//         q->last->next = newNode;
//         q->last = newNode;
//     }
    
//     // pthread_mutex_unlock(&q->mutex);
// }

// // DESENCOLAR
// int pop(Queue* q) {
//     // pthread_mutex_lock(&q->mutex);
    
//     if (q->first == NULL) { // LA COLA ESTÁ VACÍA
//         // pthread_mutex_unlock(&q->mutex);
//         return -1;
//     }
    
//     Node* temp = q->first;
//     int msg = temp->data;
    
//     if (q->first == q->last) { // LA COLA SOLO TIENE 1 ELEMENTO

//         q->first = q->last = NULL; // LA COLA QUEDA VACIA

//     } else {

//         q->first = q->first->next; // SALE EL PRIMERO DE LA COLA Y EL PRIMERO PASA A SER EL SEGUNDO

//     }
    
//     free(temp); // LIBERAR MEMORIA

//     // pthread_mutex_unlock(&q->mutex);
    
//     return msg;
// }