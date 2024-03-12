#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
int main() {
    int pipefd[2];
    pid_t child_pid;
    int num;

    // Crearea pipe-ului
    if (pipe(pipefd) == -1) {
        perror("Error creating pipe");
        exit(1);
    }

    // Crearea procesului copil
    child_pid = fork();

    if (child_pid == -1) {
        perror("Error on fork");
        exit(1);
    }

    if (child_pid == 0) {
        // Procesul copil

        close(pipefd[1]); // Copilul nu va scrie pe pipe

        read(pipefd[0], &num, sizeof(int)); // Citirea numărului de la părinte

        if (num % 2 == 0) {
            printf("Proces copil: Numarul %d este par.\n", num);
        } else {
            printf("Proces copil: Numarul %d este impar.\n", num);
        }

        close(pipefd[0]);
        exit(0);
    } else {
        // Procesul părinte

        close(pipefd[0]); // Părintele nu va citi de pe pipe

        printf("Proces parinte: Introduceti un numar: ");
        scanf("%d", &num);

        write(pipefd[1], &num, sizeof(int)); // Trimiterea numărului către copil

        close(pipefd[1]);
        wait(NULL); // Așteptarea copilului să se termine

        printf("Proces parinte: Comunicare prin pipe finalizata.\n");
    }

    return 0;
}
