//v.2: está realizado como se explicó el curso 24/25

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>

//1 vector de sem

sem_t sem_prod, sem_consum; //declaracion sem general
sem_t sem_lleno, sem_vacio;

#define TAM_BUFFER 3
#define elem 1

int buffin=0;
int buffer[TAM_BUFFER];

int buffout=0;
int datoLeido=0;

void * productor(void *arg){
    for (int i=0; i<elem; i++){
        if(sem_wait(&sem_lleno)){
            printf("Error en sem_wait()\n");
            exit(EXIT_FAILURE);
        }
        if(sem_wait(&sem_prod)){
            printf("Error en sem_wait()\n");
            exit(EXIT_FAILURE);
        }
        //añadir();
        int aleatorioGenerado = rand()%10;
        buffer[buffin]=aleatorioGenerado;
        printf("Produciendo un %d en la posición %d\n", buffer[buffin], buffin);
        buffin=(buffin+1)%TAM_BUFFER; //recorre las pos de forma ciruclar
        //
        if(sem_post(&sem_consum)){
            printf("Error en sem_post()\n");
            exit(EXIT_FAILURE);
        }
        if(sem_post(&sem_vacio)){
            printf("Error en sem_post()\n");
            exit(EXIT_FAILURE);
        }
    }
    pthread_exit((void *) NULL);
}

void * consumidor(void *arg){
    for(int i=0; i<elem; i++){
        if(sem_wait(&sem_vacio)){
            printf("Error en sem_wait()\n");
            exit(EXIT_FAILURE);
        }
        if(sem_wait(&sem_consum)){
            printf("Error en sem_wait()\n");
            exit(EXIT_FAILURE);
        }
        //extraer();
        datoLeido=buffer[buffout];
        printf("Consumiendo un %d en la posición %d\n", datoLeido, buffout);
        buffout=(buffout+1)%TAM_BUFFER;
        //
        if(sem_post(&sem_prod)){
            printf("Error en sem_post()\n");
            exit(EXIT_FAILURE);
        }
        if(sem_post(&sem_lleno)){
            printf("Error en sem_post()\n");
            exit(EXIT_FAILURE);
        }
    }
    pthread_exit((void *) NULL);
}

int main(int argc, char *argv[]){
    int n_prod = 3, n_consum = 3;
    pthread_t thread_prod[n_prod], thread_consum[n_consum];
    srand(time(NULL));
    //i0
    if(sem_init(&sem_prod, 0, 1)){
        printf("Error en sem_init()\n");
        exit(EXIT_FAILURE);
    }
    if(sem_init(&sem_consum, 0, 1)){
        printf("Error en sem_init()\n");
        exit(EXIT_FAILURE);
    }
    if(sem_init(&sem_lleno, 0, TAM_BUFFER)){ //dice las posiciones disponibles
        printf("Error en sem_init()\n");
        exit(EXIT_FAILURE);
    }
    if(sem_init(&sem_vacio, 0, 0)){ //dice las posiciones ocupadas
        printf("Error en sem_init()\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<n_prod; i++)
        if(pthread_create(&thread_prod[i], NULL, (void *) productor, (void *) NULL) != 0){
            printf("Error en la creación\n");
            exit(EXIT_FAILURE);
        }
    for(int i=0; i<n_consum; i++)
        if(pthread_create(&thread_consum[i], NULL, (void *) consumidor, (void *) NULL) != 0){
            printf("Error en la creación\n");
            exit(EXIT_FAILURE);
        }

    for(int i=0; i<n_prod; i++)
        if(pthread_join(thread_prod[i], (void **) NULL) != 0){
            printf("Error en la recogida\n");
            exit(EXIT_FAILURE);
        }    
    for(int i=0; i<n_consum; i++)
        if(pthread_join(thread_consum[i], (void **) NULL) != 0){
            printf("Error en la recogida\n");
            exit(EXIT_FAILURE);
        }  
    
    //fin
    if(sem_destroy(&sem_prod) != 0){
        printf("Error en sem_destroy()\n");
        exit(EXIT_FAILURE);
    }  
    if(sem_destroy(&sem_consum) != 0){
        printf("Error en sem_destroy()\n");
        exit(EXIT_FAILURE);
    }  
    if(sem_destroy(&sem_lleno) != 0){
        printf("Error en sem_destroy()\n");
        exit(EXIT_FAILURE);
    }  
    if(sem_destroy(&sem_vacio) != 0){
        printf("Error en sem_destroy()\n");
        exit(EXIT_FAILURE);
    }  
    exit(EXIT_SUCCESS); 
}