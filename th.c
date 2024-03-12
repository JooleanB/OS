#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int matrix[100][100],n,m;

void *suma(void* arg){
  int index = *(int*)arg;
  int suma=0;
  // int* result = malloc(sizeof(int));
  for(int j=0;j<m;j++)
 	suma+=matrix[index][j];
  // *result = suma;
  //return  (void*) result;
   printf("MUIE: %d",suma);
   free(arg);
   return NULL;
}

int main()
{
  //int* res[100];
  int i;
  int fd = open("matrix.txt", O_RDONLY);
  read(fd,&n,sizeof(int));
  read(fd,&m,sizeof(int));
  pthread_t th[n];
  for(int k=0;k<n;k++)
	for(int j=0;j<m;j++)
		read(fd,&matrix[k][j],sizeof(int));
  for (i = 0; i < n; i++) {
    //int* arg = malloc(sizeof(int));
    // *arg = i;
    pthread_create(&th[i], NULL, suma, &i);
  }
  for(i=0;i<n;i++){
        pthread_join(th[i],NULL);
  }
  /* for(i=0;i<n;i++)
   {
  	sum+=*res[i];
        printf("Rezultat %d\n",*res[i]);
	free(res[i]);
   }
    printf("FINAL: %d\n",sum);*/
   return 0;
}
