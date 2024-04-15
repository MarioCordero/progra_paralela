#include <stdio.h>
#include <unistd.h>
// INCLUDE OF THE waitpid
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    
    

    pid_t pid = fork();

    if (pid == 0) { // when PID=0 that means that it's the child

            printf("Hello from the other side\n");

        } else {
            
            waitpid(-1, NULL, 0);
            printf("I'm your father hello, it's me\n");

        }
}