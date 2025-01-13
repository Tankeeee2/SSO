#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char **argv){
    if(argc < 2){
        printf("Error de argumentos\n");
        exit(EXIT_FAILURE);
    }
    pid_t pid;
    int n = (argc-1), status;  
    for(int i=0; i<n; i++){
        pid = fork();
        switch(pid){
            case -1:
                perror("Error en el fork\n");
                exit(EXIT_FAILURE);

            case 0:
                printf("Soy %dº hijo con PID %ld y mi padre es %ld\n\n", i+1, (long int)getpid(), (long int)getppid());
                if(i==0){
                    if(execlp("gnome-calculator", "gnome-calculator", NULL) == -1){
                        perror("Error en execlp\n");
                        exit(EXIT_FAILURE);
                    }

                    if(execlp(argv[1], argv[1], NULL) == -1){
                        perror("Error en execlp\n");
                        exit(EXIT_FAILURE);
                    }
                }else{
                    if(execvp("gedit", &argv[2]) == -1){
                        perror("Error en execvp\n");
                        exit(EXIT_FAILURE);
                    }

                    if(execvp(argv[2], &(argv)[2]) == -1){
                        perror("Error en execvp\n");
                        exit(EXIT_FAILURE);
                    }
                }
                exit(EXIT_SUCCESS);

            default:
                printf("Soy el padre con PID %ld y la terminal es %ld\n\n", (long int)getpid(), (long int)getppid());
        }
    }

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