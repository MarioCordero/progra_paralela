#include <stdio.h>
#include <unistd.h>
// INCLUDE OF THE waitpid
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {

    int status;

    printf("Main process\n");
    int n = 5;
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            printf("I'm child process number %d\n", i);
            return 0;
        }

    }

    for(int i=0 ; i<5 ; i++){
        waitpid(-1, &status, 0);
    }
    printf("DONE\n");

    return 0;
}