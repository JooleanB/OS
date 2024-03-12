#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int x;
int patrat_perfect=1;
int i=1;
pthread_mutex_t mutex;
pthread_cond_t cond;

void*  generare()
{
	pthread_mutex_lock(&mutex);
	while(patrat_perfect<x)
	{
		pthread_cond_signal(&cond);
		i++;
		patrat_perfect=i*i;
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void* comparare()
{
	pthread_mutex_lock(&mutex);
        while(patrat_perfect<x)
	{
		pthread_cond_wait(&cond,&mutex);
	}
	printf("%d este primult patrat perfect mai mare decat %d \n",patrat_perfect,x);
        pthread_mutex_unlock(&mutex);
        return NULL;
}

int main(int argc,char* argv[])
{
	x=atoi(argv[1]);
	pthread_t th[2];
	pthread_create(&th[0],NULL,generare,NULL);
	pthread_create(&th[1],NULL,comparare,NULL);
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	for(int i=0;i<2;i++)
		pthread_join(th[i],NULL);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	return 0;	
}
