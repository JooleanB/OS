#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
typedef struct{
	char str[100];
}argument;

//Scrieti un program C care converteste toate literele mici din argumentele primite la linia de comanda
// in litere mari si afiseaza rezultatul. Folositi un thread pentru fiecare argument.

void* fct(void* arg){
	int i;
	argument a =*((argument*)arg);
	for(i=0;i<strlen(a.str);i++)
		a.str[i]=toupper(a.str[i]);
	printf("Thread finished: %s\n", a.str);
	return NULL;
}

int main(int argc,char* argv[])
{
	pthread_t th[argc];
	int i;
	for(i=1;i<argc;i++){
		//int* a = malloc(sizeof(int));
		//*a=i;
		if(pthread_create(&th[i],NULL,&fct,argv[i])!=0)
			return 1;
	}
	for(i=1;i<argc;i++){
		if(pthread_join(th[i],NULL)!=0)
			return 2;
	}
 	return 0;
}
