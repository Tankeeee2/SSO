#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#define MAXTHREAD 2

int variable=0;

void* funcion_hilo();



int main(){

    
    printf("Valor de la variable: %d\n", variable);

    pthread_t hilos[MAXTHREAD];

    for(int i=0;i<MAXTHREAD;i++){
        if(pthread_create(&hilos[i], NULL, (void *)funcion_hilo, (void *)NULL) !=0){
            fprintf(stderr,"Error creando hilo\n");
            exit(EXIT_FAILURE);
        }
        
    }
    for(int i=0;i<MAXTHREAD;i++){
        if(pthread_join(hilos[i],NULL) !=0){
            fprintf(stderr,"Error creando hilo\n");
            exit(EXIT_FAILURE);
        
        }
    }
    printf("Valor de la variable: %d\n", variable);

}


void* funcion_hilo(){  
    printf("Hilo creado, soy el hilo %ld\n", (long int) pthread_self());

    for(int j=0;j<1000000;j++){
        variable++;
    }
    printf("Saliendo del hilo %ld\n", (long int) pthread_self());
    printf("aux= %d\n", variable);
    pthread_exit(NULL);

}