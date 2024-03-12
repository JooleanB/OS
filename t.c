#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
// Function to remove a vowel from the string
void removeVowel(char str[]) {
    char vowels[] = "aeiouAEIOU";
    int len = strlen(str);
    int i, j = 0;

    for (i = 0; i < len; i++) {
        if (strchr(vowels, str[i]) != NULL) {
            break;
        }
    }

    for (j = i; j < len; j++) {
        str[j] = str[j + 1];
    }
    str[len - 1] = '\0';
}

int main() {
    int verificare=1;
    int p2c[2],c2p[2], pid,marime=0;
    char sir[100];

    if (pipe(p2c) == -1) {
        printf("Pipe creation failed\n");
    }

    if (pipe(c2p) == -1) {
        printf("Pipe creation failed\n");
    }

    pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
    }
    else
        while(1){
                 if (pid > 0) {
                        close(p2c[0]);
                        close(c2p[1]);
                        if(verificare==1){
                                printf("Enter a string with more than 25 characters: ");
                                fgets(sir,100,stdin);
                                verificare=0;
                                marime=strlen(sir);
                                //printf("%d",marime);
                                //printf("SIRUL CITITI ESTE %s \n",sir);
                                write(p2c[1],&marime,sizeof(int));
                                write(p2c[1], sir, strlen(sir)+1);
                        }
                        read(c2p[0], &marime, sizeof(int));
                        read(c2p[0], sir, marime);
                        if (marime>4) {
                                //printf("Received from child: %s , %d\n", sir,marime);
                                for (int i = 0; i < marime-2; i++) {
                                        sir[i] = sir[i + 1];
                                }
                        sir[marime - 4] = '\0';
                        //printf("%ld",strlen(sir));
                        printf("PARENT: %s , %ld \n", sir,strlen(sir)+1);
                        marime = strlen(sir)+1;
                        //printf("Marime trimisa %d",marime);
                        write(p2c[1], &marime, sizeof(int));
                        write(p2c[1], sir, strlen(sir)+1);

                        }
                        // Close the write end of the pipe
                        else{
                        close(p2c[1]);
                        close(c2p[0]);
                        wait(NULL);
                        printf("Parent process finished.\n");
                        break;}
                 }
                 else {
                        // Child process

                        // Close the unused write end of the pipe
                        close(p2c[1]);
                        close(c2p[0]);

                        // Read the input string from the pipe
                        if(verificare==1)
                        {
                        read(p2c[0],&marime,sizeof(int));
                        read(p2c[0], sir, marime);
                        //printf("%d \n",marime);
                        //printf("PRIMIT DE LA PARINTE %s \n",sir);
                        verificare=0;
                        }
                        if(marime>4) {

                                // Remove a vowel from the string
                                removeVowel(sir);
                                printf("CHILD: %s,%ld",sir,strlen(sir)+1);
                                // Send the modified string back to the parent
                                marime=strlen(sir)+1;
                                //printf("MARIMEA DUPA ELIMINAREA VOCALEI ESTE  %d \n",marime);
                                write(c2p[1], &marime, sizeof(int));
                                write(c2p[1], sir, strlen(sir)+1);

                                // Read the modified string from the parent
                                read(p2c[0],&marime,sizeof(int));
                                read(p2c[0], sir, marime);
                }
                        else{
                        printf("Final string: %s\n", sir);

                        // Close the read end of the pipe
                        close(p2c[0]);
                        close(c2p[1]);
                        printf("Child process finished.\n");
                        break;}
                }
        }
    return 0;
}
