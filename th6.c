//Scrieti un program C care citeste de la tastatura un numar N si creeaza 2 thread-uri. Unul dintre thread-uri
// va genera un numar par si il va insera intr-un thread primit ca parametru. Celalalt thread va genera un numar
// impar si il va insera in acelasi sir de numere primit ca parametru. Implementati un mecanism de sincronizare 
//intre cele 2 thread-uri astfel incat alterneaza in inserarea de numere in sir, pana cand sirul contine N numere.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
//#include <random>

int n;
pthread_mutex_t mutex;
pthread_cond_t cond;

void* functie(void* arg)
{
	int* lista = (int*)arg;
	int index=0;
	pthread_mutex_lock(&mutex);
	while(index<n)
	{
	 int nr =2*(rand()%100);
	 printf("NUMARUL ADAUGAT PE POZITIE PARA ESTE : %d\n",nr);
	 lista[index]=nr;
	 index+=2;
	 pthread_cond_signal(&cond);
	 pthread_cond_wait(&cond,&mutex);
	}
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
	printf("THREAD 1 FINISHED \n");
	return NULL;
}

void* functie2(void* arg)
{
	sleep(5);
	int* lista = (int*)arg;
	int index=1;
        pthread_mutex_lock(&mutex);
	while(index<n)
        {
         int nr =2*(rand()%100)+1;
	 printf("NUMARUL ADAUGAT PE POZITIE IMPARA ESTE : %d\n",nr);
         lista[index]=nr;
         index+=2;
         pthread_cond_signal(&cond);
         pthread_cond_wait(&cond,&mutex);
        }
	pthread_mutex_unlock(&mutex);
	printf("THREAD 2 FINISHED \n");
	return NULL;
}

int main(int argc, char* argv[])
{

	scanf("%d",&n);
	pthread_t th[2];
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	int* numere = malloc(sizeof(int)*n);
	if(pthread_create(&th[0],NULL,functie,numere)!=0)
			return 1;
	if(pthread_create(&th[1],NULL,functie2,numere)!=0)
			return 1;
	for(int i=0;i<2;i++)
		if(pthread_join(th[i],NULL)!=0)
			return 2;
	return 0;
}
