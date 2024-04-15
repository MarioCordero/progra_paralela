#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// INCLUDE OF THE waitpid
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(void){

    printf("Process start\n");
    int total_forks = 8;
    char *msg = malloc(1024 * 1024 * 1024);
    memset(msg, 8, 1024 * 1024 * 1024);
    snprintf(msg, 100, "I'm the parent process!!!\n");
    printf("[Parent] The address of msg is: %p | Value is: %s\n", msg, msg);

    for (int i = 0; i < total_forks; i++){
        pid_t pid = fork();

        if (pid == 0){
            snprintf(msg, 100, "hello from child %d", i);
            memset(msg, 8, 1024 * 1024 * 1024);
            printf("[Child %d] The address of msg is: %p | Value is: %s\n", i, msg, msg);
            sleep(10);
            return 0;
        }

    }

    for (int i = 0; i < total_forks; i++){
        wait(NULL);
    }

    printf("[Parent] The program ends\n");
    printf("[Parent] The final value of msg is: %s\n", msg);
    
    return 0;
}