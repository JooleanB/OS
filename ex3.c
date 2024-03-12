#include <sys/types.h>
 #include <unistd.h>
 #include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
        int copil,pip[2],marime;
	char caracter;
	char sir[100];
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
		printf("MUIE\n");
		int nr=0;
                close(pip[1]);
                read(pip[0],&caracter,sizeof(char));
		read(pip[0],&marime,sizeof(int));
		read(pip[0],sir,marime);
                close(pip[0]);
                for(int i=0;i<strlen(sir);i++)
			if(sir[i]==caracter)
				nr++;
		printf("Numarul de aparitii al caracterului introdus este: %d",nr);
                exit(1);
        }
        else
        {
                close(pip[0]);
                printf("Introduceti un caracter\n");
                scanf("%c",&caracter);
		printf("Introduceti un sir de caractere\n");
		scanf("%s",sir);
                write(pip[1],&caracter,sizeof(char));
		marime=sizeof(sir);
		write(pip[1],&marime,sizeof(int));
		write(pip[1],sir,sizeof(sir));
                close(pip[1]);
                wait(NULL);
        }
return 0;
}
