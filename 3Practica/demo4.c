/*
A continuacion se expone un programa de sincronización entre hilos.
Este programa suma los números impares entre 0 y 20, es decir, 
los números 1+3+5+7+9+11+13+15+17+19 = 100.
El primer hilo comprueba que el número es impar, si lo es deja que el
segundo hilo lo sume, sino comprueba el siguiente número.

Este programa no posee el adecuado control de errores a partir de la
documentación disponible en OpenGroup. Se deja para el lector la
ampliación del ejercicio para mejorar el control de errores.

LA HEBRA P1 SOLO QUEDARÁ BLOQUEADA CUANDO EL NUMERO SEA IMPAR,
Y ESO SERA ASI HASTA QUE LA HEBRA P2 LA DESBLOQUEE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s1; //Semáforo s1 para acceder a SC cuando el numero es impar. 
sem_t s2; //Semáforo s2 para acceder a SC cuando el numero es par. 
int num=0, suma=0; //Recurso compartido o sección crítica

void *p1(void * a){
    //El hilo 1 comprueba todos los numeros entre el 1 y el 20
    for (int i=1; i<=20; i++){
		/*Cuando haya que sumar un impar se bloqueará aquí hasta que termine P2. 
        La primera vez que entra no se bloquea, esta inicializado a 1*/
		
        if ( (i%2)!= 0){ /*Si el resultado es distinto de cero (cierto en C) es que es impar. */ 
            sem_wait (&s1);
            num=i; //Seccion critica
            printf ("HILO1: Número impar %d. Desbloqueando a HILO 2\n", i); 
			sem_post (&s2); //Si p2() está esperando en s2, P2 se desbloqueará.

        }
    }
    pthread_exit(NULL); 
}


void *p2(void * a){
    //Entre 1 y 20 hay 10 números impares, por tanto un bucle de 10 iteraciones
    for (int i=0; i<10; i++){
        /*Se queda esperando cuando el número es par y lo tiene que desbloquear P1 cuando
         encuentre un impar, ya que “num” tendra el valor impar a sumar*/

        sem_wait (&s2);
        printf ("HILO2: Suma actual = %d + %d = %d\n", suma, num, (suma+num));
        suma = suma+num; //Seccion critica
        
        /*Cuando haya sumado un impar desbloqueará a P1() incrementando s1 para que busque
        el siguiente impar. P1 se encontrará esperando a que P2 haga la suma antes de poder
        volver a entrar en la sección crítica*/
        

        sem_post (&s1);        
    }
    pthread_exit(NULL); 
}


int main(){
    int error1, error2;
    pthread_t h1, h2;
    //Complete el control de errores
	// ... 
    if(sem_init(&s1, 0, 1)!=0){ //Semáforo de impares inicializado a 1 
        printf("Error al inicializar el semaforo de impares\n");
        exit(EXIT_FAILURE);
    }
    if(sem_init(&s2, 0, 0)!=0){ //Semáforo de pares inicializado a 0 por si el hilo 2 va mas rapido que el 1 
        printf("Error al inicializar el semaforo de pares\n");
        exit(EXIT_FAILURE);
    }

    //Note que podría hacer esto con un bucle for(), mejorelo y complete el control de errores.
    if(pthread_create(&h1, NULL, p1, NULL)!=0){
        printf("Error al crear el primer hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&h2, NULL, p2, NULL)!=0){
        printf("Error al crear el segundo hilo\n");
        exit(EXIT_FAILURE);
    } 
    //Complete el control de errores
    // ...
    
    //Note que podría hacer esto con un bucle for(), mejorelo y complete el control de errores.
    if(pthread_join (h1, NULL)!=0){
        printf("Error al esperar el primer hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join (h2, NULL)!=0){
        printf("Error al crear el segundo hilo\n");
        exit(EXIT_FAILURE);
    }
    //Complete el control de errores
    // ...
    
    printf ("Main() - La suma es %d\n", suma);
	exit(EXIT_SUCCESS);
}