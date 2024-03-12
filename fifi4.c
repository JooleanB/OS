#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
int main()
{
   int fd_read =open("a-b",O_RDONLY);
    if(fd_read==-1)
   {
        printf("EROARE OPEN\n");
        return 1;
   }
    int fd_write = open("b-a",O_WRONLY);
   if(fd_write==-1)
   {
        printf("EROARE OPEN\n");
        return 1;
   }
   int n;
   if(read(fd_read,&n,sizeof(int))==-1)
     {
        printf("EROARE WRITE\n");
        return 0;
     }
  printf("CITIT N\n");
  char argumente[100][100];
  for(int i=1;i<n;i++){
   	if(read(fd_read,argumente[i],sizeof(char)*1000)==-1)
    	{
        	printf("EROARE READ\n");
        	return 0;
    	}
  argumente[i][strlen(argumente[i])]='\0';
 }
  printf("CITIT ARGUMENTE\n");
  for(int i=1;i<n;i++)
 {	
    int length=strlen(argumente[i]);
    for (int j = 0; j < length; j++) 
        argumente[i][j] = toupper(argumente[i][j]);
 }
 printf("ARGUMENTE MODIFICATE\n");
 for (int i=1;i<n;i++)
   {
     if(write(fd_write,argumente[i],sizeof(char)*1000)==-1)
     {
        printf("EROARE WRITE\n");
        return 0;
     }
   }
 printf("ARGUMENTE SCRISE INAPOI\n");
  close(fd_write);
 close(fd_read);
return 0;
}
