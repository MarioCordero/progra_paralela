#include <stdio.h>
#include <unistd.h>
int main(void) {
    
    printf("\n\n\n\n\n");
    printf("HELLO");

    pid_t pid = fork();

    if (pid == 0) { // when PID=0 that means that it's the child

            printf("Hello from the other side\n");

        } else {
            
            printf("Hello, it's me\n");

        }

    printf("\n\n\n\n\n");
}