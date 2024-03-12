#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int boltz(int nr)
{
  if(nr%7==0)
	return 1;
  int c=0;
  while(nr)
	{
	  c=nr%10;
	  nr/=10;
	  if(c==7)
	    return 1;
	}
  return 0;

}

void play(int pipes[][2],int index,int n)
{
  int r=index%n;
  int w=(index+1)%n;
  for(int i=0;i<n;i++)
  {
    if(i!=r)
	close(pipes[i][0]);
    else if(i!=w)
	close(pipes[i][1]);
  }
  if(index==0)
  { 
   printf("START\n");
   write(pipes[w][1],&n,sizeof(int));
  }
  while(n<1000)
  {
    read(pipes[r][0],&n,sizeof(int));
    n++;
    if(boltz(n)==0)
    	printf("Numarul este %d \n",n);
    else
	printf("BOLTZ\n");
    write(pipes[w][1],&n,sizeof(int));
  }
  wait(0);
  close(pipes[r][0]);
  close(pipes[w][1]);
}
int main()
{
	int n,i;
	printf("Introduceti un numar\n");
	scanf("%d",&n);
	int pipes[n][2];
	for(i=0;i<n;i++)
		if(pipe(pipes[i])==-1)
			{printf("EROARE PIPE\n");
			return 0;}
	for(i=0;i<n;i++)
	{
		int f=fork();
		if(f==-1)
			printf("EROARE FORK\n");
		else if(f==0)
			break;
	}
	if(i < n)
            play(pipes, i, n);

	return 0;
}
