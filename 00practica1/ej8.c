#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

void funcionManejadora(){
    printf("HIJO: He recibido la señal SISGUR1(%d) de mi padre y la ignoro\n", SIGUSR1);
}

int main(){
    pid_t pid;
    pid = fork();
    switch(pid){
        case -1:
            printf("fork error\n");
            exit(EXIT_FAILURE);
        case 0:
            signal(SIGUSR1, funcionManejadora);
            printf("Soy el hijo %ld y mi padre es %ld\n", (long int)getpid(), (long int)getppid());
            while(1){
                pause();
            }
            exit(EXIT_SUCCESS);
        default:
            printf("Soy el padre %ld\n", (long int)getpid());
            for(int i=0; i<4; i++){
                //kill(getpid(), SIGUSR1);
                sleep(1);
                kill(pid, SIGUSR1);
            }
            sleep(1);
            kill(pid, SIGKILL);
    }
    int status;
    while((pid = waitpid(-1, &status, WUNTRACED|WCONTINUED) )> 0){
        if(WIFEXITED(status)){
            printf("El hijo ha terminado con estado: %d\n", WEXITSTATUS(status));
        }
        else if(WIFSIGNALED(status)){
            printf("El hijo ha salido con la señal: %d\n", WTERMSIG(status));
        }
    }
    if(errno == ECHILD && pid == (pid_t)-1)
        printf("No hay más hijos que esperar\n");
    else{
        perror("Error en la invocación de waitpid\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}