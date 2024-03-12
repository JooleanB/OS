#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main (int argc, char *argv[]) {
  
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
 if (argc==3)
  {
  char string[100];
  if(0 > read(fd_read, string, sizeof(char)*100)) {
      perror("Error on read from child");
    }
 int lungime=strlen(string);
 if(0 > write(fd_write, &lungime, sizeof(int))) {
      perror("Error on read from child");
    }
 }
 else if(argc==4)
 {
  int lungime;
  if(0 > write(fd_write, argv[3], sizeof(char)*100)) {
      perror("Error on read from child");
    }
  if(0 > read(fd_read, &lungime, sizeof(int))) {
      perror("Error on read from child");
    }
  printf("Lungimea este %d",lungime);
 }
 close(fd_write);
 close(fd_read);
}
