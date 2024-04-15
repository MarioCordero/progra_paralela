#include <stdio.h>
#include <unistd.h>
int main(void) {

    printf("Main process\n");
    int n = 5;
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            printf("I'm child process number %d\n", i);
            return 0;
        }

    }

    printf("DONE\n");

    return 0;
}