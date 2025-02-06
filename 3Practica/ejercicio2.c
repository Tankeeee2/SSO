#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
int variable = -1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Iniciar mutex
void *Escritor(void *t){
    int s, cantidad;
    int *x;
    x = (int *)t;
    for (int i = 0; i < (*x); ++i)
    {
        pthread_mutex_lock(&mutex);
        cantidad = rand() % 10 + 1;
        variable = cantidad;
        printf("-->Escritor %ld, escribo el numero %d\n", pthread_self(), variable);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *Lector(void *t){
    int s, cantidad;
    int *x;
    x = (int *)t;
    for (int i = 0; i < (*x); ++i)
    {
        pthread_mutex_lock(&mutex);
        printf("<--Lector%ld, leo el numero %d\n", pthread_self(), variable);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    srand(time(NULL)); // Semilla numeros aleatorios
    int n_iteraciones;
    if (argc != 2)
    {
        printf("Error en la linea de comandos\n");
        printf("./exe n_iteraciones\n");
        exit(EXIT_FAILURE);
    }
    n_iteraciones = atoi(argv[1]);
    pthread_t hilo[2];
    for (int i = 0; i < 2; ++i)
    {
        if (i == 0)
        {
            if (pthread_create(&hilo[i], NULL, (void *)Escritor, (void *)&n_iteraciones))
            {
                printf("Error a la de crear un hilo\n");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            if (pthread_create(&hilo[i], NULL, (void *)Lector, (void *)&n_iteraciones))
            {
                printf("Error a la de crear un hilo\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    for (int i = 0; i < 2; ++i)
    {
        if (pthread_join(hilo[i], NULL))
        {
            printf("Error en la espera de la hebra-->Codigo de error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}