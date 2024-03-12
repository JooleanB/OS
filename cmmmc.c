#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
int cmmmc(int a, int b)
{
    int produs = a * b;
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    int rez = produs / a;
    return rez;
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        printf("NR INSUFICIENT DE ARGUMENTE\n");
        return 0;
    }

    int nr1 = atoi(argv[1]);
    int nr2 = atoi(argv[2]);
    printf("NUMERELE SUNT %d, %d",nr1,nr2);
    int rez = cmmmc(nr1, nr2);
    //printf("%d",rez);
    //printf("%s",argv[3]);
    //char result[20];
    //sprintf(result, "%d", rez);
    //result[strlen(result)] = '\0';

    FILE* fd = fopen(argv[3], "w");
    if (fd == NULL)
    {
        printf("Error description: %s\n", strerror(errno));
        printf("EROARE DESCHIDERE FISIER\n");
        return 0;
    }
    printf("REZULTAT : %d \n",rez);
    fprintf(fd,"%d",rez);
    fclose(fd);
    return 0;
}
