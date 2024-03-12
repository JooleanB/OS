#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	int n;
	printf("INTRODUCETI UN NUMAR\n");
	scanf("%d",&n);
	int pid=fork();
	for(int i=0;i<n;i++)
	{	
		if(pid==0)
		{
			printf("Parinte %d, Copil %d \n",getppid(),getpid());
			pid=fork();
		}
	}
	for(int i=0;i<n;i++)
		wait(NULL);
	//printf("SFARSIT");
}

