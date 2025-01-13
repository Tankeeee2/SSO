#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

pthread_mutex_t sem_par, sem_impar;
int par=0, impar=0;

void * funcion(void * dato){
    int *suma = malloc(sizeof(int*)), *indice = (int *) dato, v_num[5];
    
    if(*indice%2 == 0){
        if(pthread_mutex_lock(&sem_par) != 0){
            printf("Error en el bloqueo de sem_par\n");
            exit(EXIT_FAILURE);
        }
        for(int j=0; j<5; j++){
            v_num[j]=rand()%10;
            *suma+= v_num[j];
        }

        par += *suma;
        if(pthread_mutex_unlock(&sem_par) != 0){
            printf("Error en el desbloqueo de sem_par\n");
            exit(EXIT_FAILURE);
        }
    }
    else{
        if(pthread_mutex_lock(&sem_impar) != 0){
            printf("Error en el bloqueo de sem_impar\n");
            exit(EXIT_FAILURE);
        }
        for(int j=0; j<5; j++){
            v_num[j]=rand()%10;
            *suma+= v_num[j];
        }

        impar += *suma;
        if(pthread_mutex_unlock(&sem_impar) != 0){
            printf("Error en el desbloqueo de sem_impar\n");
            exit(EXIT_FAILURE);
        }
    }
    pthread_exit((void *) suma);
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("Error en la linea de arg\n");
        exit(EXIT_FAILURE);
    }
    int n = atoi(argv[1]), suma_par=0, suma_impar=0;
    pthread_t thread[n];
    srand(time(NULL));

    //i0
    if(pthread_mutex_init(&sem_par, NULL) != 0){
        printf("Error en la inicializacion del mutex_sum\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_mutex_init(&sem_impar, NULL) != 0){
        printf("Error en la inicializacion del mutex_resta\n");
        exit(EXIT_FAILURE);
    }
    int indice[n];
    for(int i=0; i<n; i++){
        indice[i]=i+1;
        if(pthread_create(&thread[i], NULL, (void *) funcion, (void *) &indice[i]) != 0){
            printf("Error en la creación\n");
            exit(EXIT_FAILURE);
        }
    }

    int *dato;
    for(int i=0; i<n; i++){
        if(pthread_join(thread[i], (void **) &dato) != 0){
            printf("Error en la recogida\n");
            exit(EXIT_FAILURE);
        }        
        indice[i]=i+1;
        if(indice[i]%2 == 0)
            suma_par += *dato;
        else
            suma_impar += *dato;
        printf("Main: La hebra de orden de creacion %d devolvió el valor de suma: %d\n", i+1, *dato);
    }
    printf("\nMain: Valor de la variable compartida impar: %d\n", impar);
    printf("Main: Suma de los valores devueltos por las hebras de creación impares: %d\n", suma_impar);
    
    printf("\nMain: Valor de la variable compartida par: %d\n", par);
    printf("Main: Suma de los valores devueltos por las hebras de creación pares: %d\n", suma_par);

    //fin
    if(pthread_mutex_destroy(&sem_par) != 0){
        printf("Error en la destruccion del sem_par\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_mutex_destroy(&sem_impar) != 0){
        printf("Error en la destruccion del sem_impar\n");
        exit(EXIT_FAILURE);
    }
    free(dato);
    exit(EXIT_SUCCESS);
}