#include <stdio.h>
#include <stdlib.h>
 #include <sys/types.h>
       #include <unistd.h>
//#include <sys/types>
int main(int argc,char* argv[])
{
 if(argc!=2)
	{printf("EROARE");
	return 0;}
 int nr,p2c[2],c2p[2];
 nr=atoi(argv[1]);
 int vector[nr];
 //for(int i=0;i<nr;i++)
//	vector[i]=rand();
 if(pipe(p2c)==-1)
{
 printf("EROARE PIPE\n");
 return 0;
}
if(pipe(c2p)==-1)
 {
 printf("EROARE PIPE\n");
  return 0;
}
 int pid = fork();
 if(pid==-1)
 {
 printf("EROARE FORK\n");
 return 0;
  }
 else if(pid==0)
 {
  int sum=0;
  close(p2c[1]);
  close(c2p[0]);
  read(p2c[0],&nr,sizeof(int));
  for(int i =0;i<nr;i++)
	{read(p2c[0],&vector[i],sizeof(int));
         sum+=vector[i];}
  printf("SUMA ESTE %d\n",sum);
  float rez =sum/nr;
  write(c2p[1],&rez,sizeof(float));
  close(p2c[0]);
  close(c2p[1]);
 }
 else{
  float rez;
  close(p2c[0]);
  close(c2p[1]);
  for(int i=0;i<nr;i++)
     {vector[i]=rand()%100;
	printf("P: NUMARUL ESTE %d \n",vector[i]);}
  write(p2c[1],&nr,sizeof(int));
  for(int i=0;i<nr;i++)
    write(p2c[1],&vector[i],sizeof(int));
  read(c2p[0],&rez,sizeof(float));
  printf("REZULTATUL ESTE %f",rez);
 }
 return 0;
}
