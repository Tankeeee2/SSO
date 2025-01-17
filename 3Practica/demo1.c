#include <pthread.h> 
#include <stdlib.h> 
#include <stdio.h>



int glob = 0; //GLOBAL VARIABLE
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER; //MUTEX YA INICIALIZADO A 1
pthread_t t1, t2; 


void * threadFunc(void *arg){
    int loops = *((int *) arg); 
    int hilo;
    if(pthread_self()==t1)
        hilo=1;
    else
        hilo=2;

    
    for (int j = 0; j < loops; j++){

        if (pthread_mutex_lock(&mtx)!= 0){//Bloqueamos semáforo
            printf("Mutex_lock error...\n");
            pthread_exit(NULL);
        }    
        
         /*Critical Section */
        glob++;
        /*Critical Section */
        
        printf("Hilo %d incrementando la variable, con id %ld\n", hilo,(unsigned long) pthread_self()); 

		
        if (pthread_mutex_unlock(&mtx)!= 0){//Desbloqueamos semáforo
            printf("Mutex_unlock error...\n");
            pthread_exit(NULL);
        } 

    }

    pthread_exit(NULL); 

}

int main(int argc, char *argv[]) 
{

    int loops;
    
    if(argc!=2){
        printf("Ussage: ./a.out Number_of_loops\n");
        exit(EXIT_FAILURE); 
    }
    
    loops = atoi(argv[1]);
     
    if (pthread_create(&t1, NULL, threadFunc, &loops)!= 0){
        printf("pthread_create error...\n");
        exit(EXIT_FAILURE);
    } 
    if (pthread_create(&t2, NULL, threadFunc, &loops)!= 0){
        printf("pthread_create error...\n");
        exit(EXIT_FAILURE);
    } 
    
    printf("MAIN Thread, arriving to the join call...\n"); 

    if (pthread_join(t1, NULL)!= 0){
        printf("pthread_join error...\n"); 
        exit(EXIT_FAILURE);
    }    
    if (pthread_join(t2, NULL)!= 0){
        printf("pthread_join error...\n"); 
        exit(EXIT_FAILURE);
    }   
    
    printf("MAIN Thread leaves join calls, the global variable is:%d\n", glob);

    exit(EXIT_SUCCESS); 
}