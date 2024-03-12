#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//Scrieti un program care primeste la linia de comanda siruri de caractere. Pentru fiecare sir de caractere
//programul creeaza un thread care calculeaza numarul de cifre, litere si caractere speciale
// (orice nu e litera sau cifra). Programul principal asteapta ca thread-urile sa isi incheie executia si afiseaza
// rezultatele totale (numarul total de cifre, litere si caractere speciale din toate argumentele primite
// la linia de comanda) si apoi se incheie. Folositi sincronizare eficienta. Nu folositi variabile globale.
typedef struct {
	int* litere;
	int* cifre;
	int* speciale;
	char* str;
}car;

void* fct(void* arg){
        car stringu =*((car*)arg);
        int i,len=strlen(stringu.str);
        for(i=0;i<len;i++)
                if((stringu.str[i]>='a' && stringu.str[i]<='z') || (stringu.str[i]>='A' && stringu.str[i]<='Z'))
			*(stringu.litere)+=1;
		else if( stringu.str[i]>='0' && stringu.str[i]<='9')
			*(stringu.cifre)+=1;
		else
			*(stringu.speciale)+=1;
        return NULL;
}

int main(int argc,char* argv[])
{
        int i;
        pthread_t th[argc];
	int *litere = malloc(sizeof(int));
        int *cifre = malloc(sizeof(int));
    	int *speciale = malloc(sizeof(int));
	car *args = malloc(sizeof(car) * (argc));
        for(i=1;i<argc;i++){
		args[i].litere = litere;
        	args[i].cifre = cifre;
        	args[i].speciale = speciale;
        	args[i].str = argv[i];
                if(pthread_create(&th[i],NULL,&fct,(void*)&args[i])!=0)
                        return 1;
        }
        for(i=1;i<argc;i++){
                if(pthread_join(th[i],NULL)!=0)
                        return 2;
        }
	printf("Total letters: %d\nTotal digits: %d\nTotal special characters: %d\n", *litere, *cifre, *speciale);
	free(args);
	free(litere);
	free(cifre);
	free(speciale);
        return 0;
}
