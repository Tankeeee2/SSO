#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

//Declaración de una estructura
struct param {
    char frase[30];
    int numero; 
};

/*Función que se asignará a los hilos que se creen. Recibe un puntero a estructura */ 
void *hiloMensaje(void *mensa) {
    struct param *aux = (struct param *)mensa; 
    printf("%s %d\n", aux->frase, aux->numero);

    // Las lineas anteriores se pueden sustituir por esta otra
    // printf("%s %d\n", ((struct param *)mensa)->frase, ((struct param *)mensa)->numero); 

    pthread_exit(NULL); // Fin de la hebra sin devolver nada
}

int main() {
    // Declaración de dos hebras, hilos o procesos ligeros. NO CREACION 
    pthread_t threads[2];
    struct param params[2];

    printf("Mi PID es: %d\n", getpid());

    // Inicialización de las estructuras de tipo “struct param”
    params[0] = (struct param){"Soy el hilo ", 1};
    params[1] = (struct param){"Soy el hilo ", 2};

    // Creación de hilos mediante bucle for
    for(int i = 0; i < 2; i++) {
        if(pthread_create(&threads[i], NULL, hiloMensaje, (void *)&params[i])) {
            fprintf(stderr, "Error creating thread %d\n", i + 1);
            exit(EXIT_FAILURE);
        }
    }

    // Esperamos la finalización de los hilos mediante bucle for
    for(int i = 0; i < 2; i++) {
        if(pthread_join(threads[i], NULL)) {
            fprintf(stderr, "Error joining thread %d\n", i + 1);
            exit(EXIT_FAILURE);
        }
    }

    printf("Hilo principal: han finalizado las threads.\n");
    exit(EXIT_SUCCESS);
}
