#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int var = 0;
//pthread_mutex_t mutex_bin

void *funcion(){
    for(int i=0; i<100000; i++){
        //pthread_mutex_lock(&mutex_bin); //0-> funcionamiento correcto
        var++;
        //pthread_mutex_unlock(&mutex_bin); //0-> funcionamiento correcto
    }
    printf("Soy el hilo %lu\n", pthread_self());
    pthread_exit((void*) NULL);
}

int main(){
    pthread_t thread[2];

    //Inicialización del semáforo
    //pthread_mutex_init(&mutex_bin, NULL); //0-> funcionamiento correcto

    for(int i=0; i<2; i++){
        if(pthread_create(&thread[i], NULL, (void *)funcion, (void *) NULL) != 0){
            perror("Error en la creacion del hilo\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i=0; i<2; i++){
        if(pthread_join(thread[i], (void **) NULL) != 0){
            perror("Error en la espera del hilo\n");
            exit(EXIT_FAILURE);
        }
    }

    //Inicialización del semáforo
    //pthread_mutex_destroy(&mutex_bin); //0-> funcionamiento correcto

    printf("var = %d\n", var);
    exit(EXIT_SUCCESS);
}