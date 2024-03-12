#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
 int c1_c2[2],c2_c1[2],pid1=0,pid2=0;
 if(pipe(c1_c2)==-1)
 {
  printf("EROARE PIPE\n");
  return 0;
 }
 if(pipe(c2_c1)==-1)
 {
  printf("EROARE PIPE\n");
  return 0;
 }
 pid1=fork();
 if(pid1==-1)
 {
  printf("EROARE FORK\n");
  return 0;
 }
 else if(pid1==0)
 {
  close(c1_c2[0]);
  close(c2_c1[1]);
  int n=0;
  while(n!=10)
  { 
    n = rand()%10+1;
    write(c1_c2[1],&n,sizeof(int));
    if(n==10)
      break;
    read(c2_c1[0],&n,sizeof(int));
    printf("COPILUL 2 A TRIMIS %d \n",n);
    if(n==10)
      break;
  }
  close(c1_c2[1]);
  close(c2_c1[0]);
  exit(0);
 }
 
pid2=fork();
 if(pid2==-1)
 {
  printf("EROARE FORK\n");
  return 0;
 }
 else if(pid2==0)
 {
  close(c1_c2[1]);
  close(c2_c1[0]);
  int n=0;
  while(n!=10)
  {
   read(c1_c2[0],&n,sizeof(int));
   printf("COPILUL 1 A TRIMIS %d \n",n);
   if(n==10)
     break;
   n=rand()%10+1;
   write(c2_c1[1],&n,sizeof(int));
   if(n==10)
    break;
  }
  close(c1_c2[0]);
  close(c2_c1[1]);
  exit(0);
 }
 wait(NULL);
 wait(NULL);
 return 0;
}
