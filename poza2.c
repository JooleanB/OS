#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char* argv[])
{
 if(argc!=2)
 {
	printf("NR GRESIT DE ARGUMENTE\n");
        return 1;
 }
 int pip[2],pid,nr1,nr2;
 char c;
 if(pipe(pip)==-1)
  {
   printf("EROARE PIPE\n");
   return 1;
  }
 pid=fork();
 if(pid==-1)
 {
  printf("EROARE FORK\n");
  return 1;
 }
 else if(pid==0)
 {
  close(pip[1]);
  while(1)
  {
	if(read(pip[0],&c,sizeof(char))==-1)
   	{
     	 printf("EROARE READ\n");
     	 return 1;
   	}
        if(c=='\0')
          break;
  	if(read(pip[0],&nr1,sizeof(int))==-1)
   	{
     	 printf("EROARE READ\n");
     	 return 1;
   	}
    	if(read(pip[0],&nr2,sizeof(int))==-1)
   	{
     	  printf("EROARE READ\n");
     	  return 1;
   	}
   	if(c=='+')
   	{
     	  int sum= nr1+nr2;
     	  printf("%d + %d = %d\n",nr1,nr2,sum);
   	}
   	else if(c=='-')
   	{
     	  int dif = nr1-nr2;
     	  printf("%d - %d = %d\n",nr1,nr2,dif);
   	}
   }
   close(pip[0]);
   exit(0);
 }
 else{
   close(pip[0]);
   FILE* fd = fopen(argv[1],"r");
   
   while(fscanf(fd, "%c %d %d\n",&c,&nr1,&nr2)!=-1)
   {	if(write(pip[1],&c,sizeof(char))==-1)
   	{
     	printf("EROARE write\n");
     	return 1;
   	}
   	if(write(pip[1],&nr1,sizeof(int))==-1)
   	{
     	 printf("EROARE write\n");
     	 return 1;
   	}
   	if(write(pip[1],&nr2,sizeof(int))==-1)
   	{
     	  printf("EROARE write\n");
     	  return 1;
   	}
  	//close(pip[1]);
   }
   char stop='\0';
   if(write(pip[1],&stop,sizeof(char))==-1)
        {
        printf("EROARE write\n");
        return 1;
        } 
   close(pip[1]);
 }
 wait(NULL);
 return 0;
}
