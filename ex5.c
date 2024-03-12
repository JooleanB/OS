#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    char sir[100],stringg[1000]={0};
    int pid, nr, pip[2], marime;

    if (pipe(pip) == -1) {
        printf("EROARE: pipe\n");
        return 1;
    }

    pid = fork();
    if (pid == -1) {
        printf("EROARE: fork\n");
        return 1;
    } else if (pid == 0) {
        close(pip[1]);
        read(pip[0], &marime, sizeof(int));
        read(pip[0], stringg, marime);
	close(pip[0]);
        execl("./reversed", "./reversed", argv[1], stringg, NULL);
        printf("EROARE: ./reversed\n");
	exit(1);
    } else {
        close(pip[0]);
        printf("Introduceti un numar:\n");
        scanf("%d", &nr);
        printf("Introduceti n stringuri:\n");
        for (int i = 0; i < nr; i++) {
            scanf("%s", sir);
	    strcat(stringg, sir);
	    strcpy(sir,"");
	}
	printf("%s",stringg);
	marime=strlen(stringg)+1;
        write(pip[1], &marime, sizeof(int));
        write(pip[1], stringg, marime);
        close(pip[1]);
        wait(NULL);
    }

    return 0;
}
