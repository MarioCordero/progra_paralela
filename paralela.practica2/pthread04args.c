#include <stdio.h>
#include <pthread.h>

struct arguments{
    int a;
    int b;
};

void *sum(void *arg){

    struct arguments *args = (struct arguments *)arg;
    int result = args->a + args->b;
    printf("Result: %d\n", result);
    pthread_exit(NULL);

}

int main(void){

    pthread_t thread;
    struct arguments args = {42, 23};
    
    if (pthread_create(&thread, NULL, sum, &args) != 0){

        perror("Error creating thread\n");
        return 1;

    }

    pthread_join(thread, NULL);
    return 0;

}