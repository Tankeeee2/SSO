#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    if(argc < 2){
        printf("Error de argumentos\n");
        exit(EXIT_FAILURE);
    }
    pid_t pid;
    int status;
    for(int i=2; i<=(argc-1); i++){
        pid = fork();
        switch(pid){
            case -1:
                perror("fork error\n");
                exit(EXIT_FAILURE);

            case 0:
                printf("Soy el hijo %d con PID %ld y mi padre es %ld\n\n", i+1, (long int)getpid(), (long int)getppid());
                if(execlp(argv[1], argv[1], argv[i], NULL) == -1){
                    perror("execvp error\n");
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
            default:
                printf("Soy el padre con PID %ld y la terminal es %ld\n\n", (long int)getpid(), (long int)getppid());
        }
    }
    while((pid = waitpid(-1, &status, WUNTRACED) )> 0){
        if(WIFEXITED(status))
            printf("Soy el padre con PID %ld y el hijo con pid %d ha finalizado con status %d\n", (long int)getpid(), pid, WEXITSTATUS(status));
    }
}