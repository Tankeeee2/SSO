#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argn, char *argv[]){
    if(argn!=3){
        printf("Espabila pistola que hay que pasar 2 argumentos");
        exit(EXIT_FAILURE);
    }
    printf("Hola, soy el proceso padre, con pid: %d\n",getpid());
    pid_t pid[2],hijo;
    int status;
    for(int i=0;i<2;i++){
        pid[i]=fork();
        switch(pid[i]){
            case -1:
            perror("Error en el fork\n");
            printf("ERRNO: %d",errno);
            exit(EXIT_FAILURE);
            case 0:
            if(i==0){
                printf("Soy el primer hijo con pid: %d\n",getpid());
                if(execlp(argv[1],argv[1],NULL)==-1){
                    perror("Error en execlp\n");
                    printf("ERRNO:",errno);
                }
                exit(EXIT_SUCCESS);
            }else{
                printf("Soy el segundo hijo, con pid: %d\n",getpid());
                execlp(argv[2],argv[2],NULL);
                exit(EXIT_SUCCESS);
            }
            default:
            break;
        }
    }
    while((hijo=(wait(&status)))>0){
        if(WIFEXITED(status)){
            printf("Proceso padre, con pid %d, hijo terminado con pid %ld terminado, con estado: %d\n",getpid(),(long int)hijo,WEXITSTATUS(status));
        }
        if(WIFSIGNALED(status)){
            printf("Proceso padre, con pid %d, hijo con pid %ld terminado por señal: %d\n",getpid(),(long int)hijo,WTERMSIG(status));
        }

    }
    return 0;
}