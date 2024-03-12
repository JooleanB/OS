#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//1.Scrieti un program C care primeste n fisiere ca argumente in linia de
//comanda. Programul va crea n thread-uri, alocate dinamic in memorie, fiecare
//thread va contoriza in 2 variabile globale numarul de litere mari si suma
//cifrelor din fisierele date ca si argument, fiecare thread va procesa
//un singur fisier, primit ca argument. Accesul ca variabilele globale se va
//face sincronizat, folosind variabile mutex.


int suma=0,litere=0;
pthread_mutex_t mute_suma;
pthread_mutex_t mute_litere;

void* functie(void* arg)
{
	char* fisier = arg;
	printf("%s",fisier);
	FILE* f = fopen(fisier,"r");
	char citit;
	while(fscanf(f,"%c",&citit)!=EOF)
{
		//printf("%c\n",citit);
		if(citit>='A' && citit<='Z')
		{
			pthread_mutex_lock(&mute_litere);
			litere++;
			pthread_mutex_unlock(&mute_litere);			
		}
		else if(citit>='0' && citit<='9')
		{
			pthread_mutex_lock(&mute_suma);
                        suma+=citit-'0';
                        pthread_mutex_unlock(&mute_suma);
		} 
		
}
	fclose(f);
	return NULL;
}

int main(int argc,char* argv[]){

	pthread_t* th= malloc(sizeof(pthread_t)*(argc-1));
	pthread_mutex_init(&mute_suma,NULL);
	pthread_mutex_init(&mute_litere,NULL);
	for(int i=0;i<argc-1;i++)
		pthread_create(&th[i],NULL,functie,argv[i+1]);
	for(int i=0;i<argc-1;i++)
		pthread_join(th[i],NULL);
	pthread_mutex_destroy(&mute_suma);
        pthread_mutex_destroy(&mute_litere);
	printf("SUMA CIFRELOR ESTE %d \n",suma);
	printf("NUMARUL LITERELOR MARI ESTE %d\n",litere);
	return 0;
}
