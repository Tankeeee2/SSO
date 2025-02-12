#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void sig_alrm(int signo)
{
	printf("Dentro de la funcion sig_alrm!!!\n");
	printf("Valor del entero recibido como parametro:%d\n",signo);
	return;	/* nothing to do, just return to wake up the pause */
}

unsigned int f1(int nsecs)
{	
	printf("Dentro de la funcion f1!!!------------------\n");
	alarm(nsecs);		/* start the timer */
	pause();			/* pause - suspend the thread until a signal is received */ 
}

int main ()
{

	/* Si la solicitud de tratamiento de senial se puede llevar a cabo, la funcion signal() devolverá 
	el nombre de la función (* void) que la tratará, en caso contrario se devuelve el valor de la macro
	SIG_ERR y se pone errno a un valor positivo*/

	signal(SIGALRM, sig_alrm);
   
   printf ("Una alarma en 3 segundos….\n");
   f1(3);
   printf ("Una alarma en 2 segundos...\n");
   f1(2);
   printf ("Fin del programa\n");
}