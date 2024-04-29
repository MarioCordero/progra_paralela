#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <stdint.h>

//Includes
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_THREADS 50000

// Estructura para los mensajes de la cola
struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int total_threads;
int points_inside_circle = 0;
int total_points;

void *throw_darts(void *arg){

    int childID = (uintptr_t)arg;
    int points_per_thread = total_points / total_threads;
    unsigned int seed = time(NULL) * (childID + 1);

    for (int i = 0; i < points_per_thread; i++){
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;
        if (sqrt(x * x + y * y) <= 1){

            points_inside_circle++;

        }
    }
    return NULL;
}

//Hacer un metodo de cola que soporte los métodos push y pop para enviar mensajes al hilo principal.
void message_queue(){
    
}
void pipe(){

}




int main(int argc, char *argv[]){

    if (argc != 3){
        printf("Uso: %s <total_points> <total_threads>\n", argv[0]);
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
        
    // Acá deberán introducir el paralelismo
    key_t key;
    int msgid;

    // Generamos una clave única para la cola de mensajes
    key = ftok("queuefile", 65);

    // Conectamos a la cola de mensajes
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Recibimos el mensaje
    msgrcv(msgid, &message, sizeof(message), 1, 0);

    throw_darts((void *)1);

    double pi = 4.0 * points_inside_circle / total_points;

    printf("Valor de pi: %f\n", pi);

    // Eliminamos la cola de mensajes
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
