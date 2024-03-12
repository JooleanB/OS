#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//Scrieti un program C care primeste ca argumente la linia de comanda numere intregi. Programul va calcula un vector
// de frecventa pentru cifrele zecimale. Pentru fiecare argument, programul va crea un thread care numara aparitiile
// fiecarei cifre si adauga numarul la pozitia corespunzatoare din vectorul de frecventa.

int vector[10]={0};
pthread_mutex_t mutex;

typedef struct{
 char* numar;
}nr;

void* fct(void* arg){
        nr argument =*((nr*)arg);
	int i,len=strlen(argument.numar);
	pthread_mutex_lock(&mutex);
	for(i=0;i<len;i++)
	{
		int cifra = argument.numar[i]-'0';
		vector[cifra]++;
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main(int argc,char* argv[])
{
        int i;
        pthread_t th[argc-1];
	pthread_mutex_init(&mutex, NULL);
	nr *argument = malloc(sizeof(nr)*(argc));
        for(i=1;i<argc;i++){
		argument[i].numar=argv[i];
                if(pthread_create(&th[i],NULL,&fct,(void*)&argument[i])!=0)
                        return 1;
        }
        for(i=1;i<argc;i++){
                if(pthread_join(th[i],NULL)!=0)
                        return 2;
        }
	for(i=0;i<10;i++)
		printf("NR DE APARITII AL CIFREI %d este %d \n",i,vector[i]);
	free(argument);
        return 0;
}
