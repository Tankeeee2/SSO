#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

void funcionManejadora(){
    printf("Padre: He recibido la señal SISGUR1(%d) de mi padre y la ignoro\n", SIGUSR1);
}

int main(){
    pid_t pid;
    
    pid=fork();
    switch(pid){
        case -1:
            printf("fork error");
            exit(EXIT_FAILURE);
        case 0:
            //signal(SIGUSR1, funcionManejadora);
            printf("HIJO: no hago nada\n");
            exit(EXIT_SUCCESS);
        default:
            signal(SIGUSR1, funcionManejadora);
            printf("Soy el padre %ld y la terminal es %ld\n", (long int)getpid(), (long int)getppid());
            while(1){
                pause();
            }
    }
    exit(EXIT_SUCCESS);
}