 #include <sys/types.h>
 #include <unistd.h>
 #include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int nr,copil,pip[2];
	if(pipe(pip)==-1)
	{
	printf("Eroare pipe\n");  
	}
	copil=fork();
	if(copil==-1)
	{
	printf("Eroare frok\n");
	}
	else if(copil==0)
	{
		close(pip[1]);
		read(pip[0],&nr,sizeof(int));
		close(pip[0]);
		if(nr%2==0)
			printf("Numarul este par\n");
		else
			printf("Numarul este impar\n");
		exit(1);
	}
	else	
	{
		close(pip[0]);
		printf("Introduceti un numar\n");
		scanf("%d",&nr);
		write(pip[1],&nr,sizeof(int));
		close(pip[1]);
		wait(NULL);
	}
return 0;
}
