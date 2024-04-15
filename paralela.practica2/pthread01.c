#include <stdio.h>
#include <pthread.h>

void *print_message(char *message){

    printf("%s\n", message);
    pthread_exit(NULL);

}

int main(void){

    pthread_t thread;
    int argument = 42;
    
    if (pthread_create(&thread, NULL, print_message, &argument) != 0){
        perror("Error creating thread\n");
        return 1;
    }
    
    pthread_join(thread, NULL);
    return 0;

}