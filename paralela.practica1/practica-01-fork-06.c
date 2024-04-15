#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// INCLUDE OF THE waitpid
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(void){

    printf("Process start\n");
    int total_forks = 10;
    char *msg = malloc(100);
    snprintf(msg, 100, "I'm the parent process!!!\n");
    printf("%s", msg);

    for (int i = 0; i < total_forks; i++){
        pid_t pid = fork();

		if (pid == 0){
			snprintf(msg, 100, "I'm child process number %d\n", i);
			printf("%s", msg);
			return 0;
		}
    }
	
    for (int i = 0; i < total_forks; i++){
        wait(NULL);
    }
	
    printf("The program ends\n");
    printf("The final value of msg is: %s\n", msg);
    return 0;
	
}
