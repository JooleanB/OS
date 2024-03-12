#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

int flag = -1;
char vow[] = "aeiouAEIOU";

void handler(int signum) {
    if (signum == SIGUSR1) {
        flag = 0;
    } else if (signum == SIGUSR2) {
        flag = 1;
    }
}

int removeVowel(char *str) {
    int len = strlen(str);
    for(int i = 0; i < len; i++) {
        if(strchr(vow, str[i]) != NULL) {
            strcpy(str + i, str + i + 1);
            str[strlen(str) - 1] = '\0';
            return 1;
        }
    }
    return 0;
}

int removeLetters(char *str) {
    int firstLetter = 0, lastLetter = strlen(str) - 1;
    int len = strlen(str);

    for(int i = 0; i < len; i++) {
        if(('a' <= str[i] && str[i] <= 'z') || ('A' <= str[i] && str[i] <= 'Z')) {
            firstLetter = i;
            break;
        }
    }

    for(int i = len - 1; i >= 0; i--) {
        if(('a' <= str[i] && str[i] <= 'z') || ('A' <= str[i] && str[i] <= 'Z')) {
            lastLetter = i;
            break;
        }
    }

    if (firstLetter < lastLetter) {
        strcpy(str + firstLetter, str + firstLetter + 1);
        str[len - 2] = '\0';

        lastLetter--;
        strcpy(str + lastLetter, str + lastLetter + 1);
        str[len - 3] = '\0';

        return 1;
    }
    
    return 0;
}

int main() {
    int p2c[2], c2p[2];
    char str[100];

    printf("String: ");
    fflush(stdout);
    read(STDIN_FILENO, str, sizeof(str));
    str[strlen(str) - 1] = '\0';

    if(strlen(str) < 25) {
        printf("String-ul trebuie sa aiba cel putin 25 de caractere.\n");
        exit(EXIT_FAILURE);
    }

    int rez = pipe(p2c);

    if (rez == -1) {
        perror("pipe() failed: ");
        exit(EXIT_FAILURE);
    }

    rez = pipe(c2p);

    if (rez == -1) {
        perror("pipe() failed: ");
        exit(EXIT_FAILURE);
    }

    int pid = fork();

    if (pid == -1) {
        perror("fork() failed: ");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(p2c[1]); close(c2p[0]);

        while (1) {
            if (flag == 1) {
                break;
            }

            read(p2c[0], str, sizeof(str));

            if (strlen(str) < 3) {
                kill(getppid(), SIGUSR1);
                break;
            }

            int removed = removeVowel(str);

            if (removed == 0) {
                kill(getppid(), SIGUSR1);
                break;
            }
            printf("[IN CHILD] String: %s\n", str);
            write(c2p[1], str, sizeof(str));
        }

        close(p2c[0]); close(c2p[1]);
        exit(0);
    }

    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);

    close(p2c[0]); close(c2p[1]);

    write(p2c[1], str, sizeof(str));

    while(1) {
        if (flag == 0) {
            break;
        }

        read(c2p[0], str, sizeof(str));
        
        if(strlen(str) < 3) {
            kill(pid, SIGUSR2);
            break;
        }

        int removed = removeLetters(str);
        
        if(removed == 0) {
            kill(pid, SIGUSR2);
            break;
        }

        printf("[IN PARENT] String: %s\n", str);
        write(p2c[1], str, sizeof(str));
    }

    wait(NULL);

    printf("Resulted string is: %s\n", str);

    close(p2c[1]); close(c2p[0]);
    return 0;
}
