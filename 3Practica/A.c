#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
void calculadora(char *f){
if (execlp(f,f,(char*)NULL)<0)//ERROR EN EXCECLP
{
perror("exec");
printf("ERRNO= %d\n",errno );
exit(EXIT_FAILURE);
}
}
void reloj(char *f){
if (execlp(f,f,(char*)NULL)<0)//ERROR EN EXCECLP
{
perror("exec");
printf("ERRNO= %d\n",errno );
exit(EXIT_FAILURE);
}
}
int main(int argc, char *argv[])
{ int n,status;
pid_t pid, hijo_pid;
if (argc!=3)
{
printf("Error en la linea de argumentos-->Ejecutable+gnome-calculator+xclock\n");
}
for (int i = 0; i < 2; ++i){
pid=fork();
if (pid==0)
{
if (i==0)
{printf("Proceso Hijo,mi pid es: %d, mi padre tiene el pid: %d y voy a abrir la calculadora
\n",getpid(),getppid());
calculadora(argv[1]);//Abrir calculadora
}
else{
printf("Proceso Hijo,mi pid es: %d, mi padre tiene el pid: %d y voy a abrir el reloj
\n",getpid(),getppid());
reloj(argv[2]);//Abrir reloj
}
}
else if (pid>0)
{
//En el examen el proceso padre no imprimia nada
}
else{
printf("ERROR EN LA LLAMADA FORK\n");
printf("ERRNO: %d\n",errno );
exit(EXIT_FAILURE);
}
}
while ( (hijo_pid=wait(&status)) > 0 )
{
if (WIFEXITED(status))
{
printf("Proceso padre %d, hijo con PID %ld finalizado, status = %d\n", getpid(), (long
int)hijo_pid, WEXITSTATUS(status));
}
else if (WIFSIGNALED(status)) //Para seniales como las de finalizar o matar
{
printf("Proceso padre %d, hijo con PID %ld finalizado al recibir la señal %d\n", getpid(),
(long int)hijo_pid, WTERMSIG(status));
}
}
if (hijo_pid==(pid_t)-1 && errno==ECHILD) //Entra cuando vuelve al while y no hay más hijos que esperar
{
printf("Proceso padre %d, no hay mas hijos que esperar. Valor de errno = %d, definido
como: %s\n", getpid(), errno, strerror(errno));
}
else
{
printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como:
%s\n", errno, strerror(errno));
exit(EXIT_FAILURE);
}
return 0;
}