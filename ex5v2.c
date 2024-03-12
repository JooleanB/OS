#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    char sir[100];
    char primul[10] = "PRIMUL";
    int pid, nr, pip[2], marime;

    if (pipe(pip) == -1) {
        printf("ERROR: Failed to create pipe\n");
        return 1;
    }

    pid = fork();
    if (pid == -1) {
        printf("ERROR: Failed to fork\n");
        return 1;
    } else if (pid == 0) {
        close(pip[1]);
        read(pip[0], &nr, sizeof(int));
        for (int i = 0; i < nr; i++) {
            if (i != 0)
                primul[0] = 'Y';
            read(pip[0], &marime, sizeof(int));
            read(pip[0], sir, marime);
            sir[marime - 1] = '\0';  // Null-terminate the string
            execl("./reversed", "./reversed", argv[1], sir, primul, NULL);
            printf("Failed to execute ./reversed\n");
            exit(1);
        }
        close(pip[0]);
        exit(0);
    } else {
        close(pip[0]);
        printf("Enter a number:\n");
        scanf("%d", &nr);
        write(pip[1], &nr, sizeof(int));
        printf("Enter strings:\n");
        for (int i = 0; i < nr; i++) {
            scanf("%s", sir);
            marime = strlen(sir) + 1;
            write(pip[1], &marime, sizeof(int));
            write(pip[1], sir, marime);
        }
        close(pip[1]);
        wait(NULL);
    }

    return 0;
}
