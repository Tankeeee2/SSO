#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char **argv){

    if(argc != 2){
        printf("Error de argumentos, introduzca 2 argumentos\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid;
    int hijos = atoi(argv[1]);
  

    for(int i=0; i<hijos; i++){
        pid = fork();
        switch(pid){
            case -1:
                perror("Error en el fork\n");
                exit(EXIT_FAILURE);

            case 0:
                printf("Soy el %dº hijo con PID %ld y mi padre es %ld\n\n", i+1, (long int)getpid(), (long int)getppid());
                printf("%ldº hijo, espero %d segundos\n", (long int)getpid(), 10*(i+1));
                sleep(10*(i+1));
                exit(EXIT_SUCCESS);
            default:
                printf("Soy el padre con PID %ld y la terminal(mi padre) es %ld\n\n", (long int)getpid(), (long int)getppid());

        }

    }

    int status;
    while((pid = waitpid(-1, &status, WUNTRACED) )> 0){
        if(WIFEXITED(status))
            printf("Soy el padre con PID %ld y mi hijo con pid %d ha finalizado con status %d\n", (long int)getpid(), pid, WEXITSTATUS(status));

    }

    if(errno == ECHILD && pid == (pid_t)-1){
        printf("No hay más hijos que esperar\n");

        }else{
            perror("Error de waitpid\n");
            exit(EXIT_FAILURE);

        }
    exit(EXIT_SUCCESS);

}