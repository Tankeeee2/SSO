#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int variable=-1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* Escritor(void *a){
    int repeticiones= *(int*) a;
    printf("Hola mis locos soy el hilo %ld y doy %d vueltas\n", (long int) pthread_self(),repeticiones);
    pthread_mutex_lock(&mutex);

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void* Lector(void *a){
    pthread_mutex_lock(&mutex);
    
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(int argn, char* argv[]){
    if(argn!=2){
        printf("Que pases 1 argumento\n");
        exit(EXIT_FAILURE);
    }
    pthread_t uno,dos;
    int a=3;
    if(pthread_create(&uno,NULL,Escritor,&a)){
        printf("Error al crear el hilo");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&dos,NULL,Lector,&a)){
        printf("Error al crear el hilo");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(uno,NULL)){
        printf("Error no termina el hilo");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(dos,NULL)){
        printf("Error no termina el hilo");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}