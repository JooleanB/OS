#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main (int argc, char *argv[]) {
  
  for(int i=1;i<argc;i++)
 { int lungime = strlen(argv[i]);
   printf("%d\n",lungime);
 }
  if (0 > mkfifo("myfifo1", 0600)) {
    perror("Error on make fifo 1");
    exit(1);
  }
  if (0 > mkfifo("myfifo2", 0600)) {
    perror("Error on make fifo 2");
    exit(1);
  }
  
  int fd_read = open(argv[1], O_RDONLY);
  if(-1 == fd_read) {
    perror("Error opening fifo 1 in A");
    exit(1);
  }
  int fd_write = open(argv[2], O_WRONLY);
  if(-1 == fd_write) {
    perror("Error opening fifo 2 in A");
    close(fd_write);
    exit(1);
  }

}
