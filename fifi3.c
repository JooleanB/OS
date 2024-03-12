#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char* argv[])
{
  if(mkfifo("a-b",0777)==-1)
   {
    	printf("EROARE FIFO\n");
        return 1;
   }
  //printf("COAIEEEEEEEEEEE\n");

   if(mkfifo("b-a",0777)==-1)
   {
        printf("EROARE FIFO\n");
        return 1;
   }
   //printf("COAIEEEEEEEE\n");
   int fd_write = open("a-b",O_WRONLY);
   if(fd_write==-1)
   {
        printf("EROARE OPEN\n");
        return 1;
   }
   printf("DESCHIS1\n");
   int fd_read =open("b-a",O_RDONLY);
    if(fd_read==-1)
   {
        printf("EROARE OPEN\n");
        return 1;
   }
    printf("DESCHIS1\n");
   if(write(fd_write,&argc,sizeof(int))==-1)
     {
        printf("EROARE WRITE\n");
        return 0;
     }
    printf("SCRIS ARGUMENTE\n");
   for (int i=1;i<argc;i++)
   {
     if(write(fd_write,argv[i],sizeof(char)*1000)==-1)
     {
   	printf("EROARE WRITE\n");
        return 0;
     }
   }
   printf("SCRIS ARGUMENTE\n");
   char argumente [100][100];
  for (int i=1;i<argc;i++){
    if(read(fd_read,argumente[i],sizeof(char)*1000)==-1)
    {
	printf("EROARE READ\n");
        return 0;
    }
  argumente[i][strlen(argumente[i])]='\0';
  
 }
  printf("CITIT ARGUMENTE\n");
  char rezultat [1000];
 for(int i=1;i<argc;i++)
 {
	strcat(rezultat,argumente[i]);
        strcat(rezultat," ");
 }
 printf("REZULTATUL: %s",rezultat);
 close(fd_write);
 close(fd_read);
 if(0 > unlink("a-b")) {
    perror("Error removing fifo 1");
  }
  if(0 > unlink("b-a")) {
    perror("Error removing fifo 2");
  }
return 0;
}
