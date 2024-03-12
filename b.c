#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int pipes[2], nr;
    pid_t child_pid;

    if (pipe(pipes) == -1)
    {
        printf("Eroare la crearea pipe-ului\n");
        exit(1);
    }

    child_pid = fork();

    if (child_pid == -1)
    {
        printf("EROARE la crearea procesului copil\n");
        exit(1);
    }
    else if (child_pid == 0)
    {
        close(pipes[1]);
        read(pipes[0], &nr, sizeof(int));
        close(pipes0]);

        if (nr == 2)
        {
            printf("Numarul este prim\n");
        }
        else if (nr < 2 || nr % 2 == 0)
        {
            printf("Numarul nu este prim\n");
        }
        else
        {
            int prim = 1;
            for (int d = 3; d * d <= nr; d += 2)
            {
                if (nr % d == 0)
                {
                    prim = 0;
                    break;
                }
            }

            if (prim)
            {
                printf("Numarul este prim\n");
            }
            else
            {
                printf("Numarul nu este prim\n");
            }
        }

        exit(0);
    }
    else
    {
        close(pipes[0]);
        printf("Introduceti un numar: ");
        scanf("%d", &nr);
        write(pipes[1], &nr, sizeof(int));
        close(pipes[1]);
        wait(NULL);
    }

    return 0;
}
