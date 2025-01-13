#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int global = 0;

int main(int argc, char **argv){
    if(argc != 2){
        printf("Error de argumentos\n");
        exit(EXIT_FAILURE);
    }
    pid_t pid;
    int n = atoi(argv[1]), status;
    for(int i=0; i<n; i++){
        pid = fork();
        switch(pid){
            case -1:
                perror("fork error\n");
                exit(EXIT_FAILURE);

            case 0:
                printf("Soy el hijo %d con PID %ld y mi padre es %ld\n\n", i+1, (long int)getpid(), (long int)getppid());
                global++;
                exit(EXIT_SUCCESS);
            default:
                printf("Soy el padre con PID %ld y la terminal es %ld\n", (long int)getpid(), (long int)getppid());
                printf("\t El valor de la variable global es %d\n\n", global);
        }
    }
    while((pid = waitpid(-1, &status, WUNTRACED) )> 0){
        if(WIFEXITED(status))
            printf("Soy el padre con PID %ld y el hijo con pid %d ha finalizado con status %d\n", (long int)getpid(), pid, WEXITSTATUS(status));
    }
    if(errno == ECHILD && pid == (pid_t)-1)
        printf("No hay más hijos que esperar\n");
    else{
        perror("Error en la invocación de waitpid\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}