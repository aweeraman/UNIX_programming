#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/errno.h>

#define BUFSIZE 4096
#define STDOUT 1

int main(int argc, char **argv) {
  int fd, n;
  char *buffer[BUFSIZE];

  if (argc < 2) {
    fprintf(stderr, "Usage: cat file-name\n");
    exit(1);
  }

  fd = open(argv[1], O_RDONLY);

  if (fd < 0) {
    perror(argv[0]);
  }

  while ((n = read(fd, buffer, BUFSIZE)) > 0) {
    if ((write(STDOUT, buffer, n)) != n) {
      perror(argv[0]);
    }
  }

  close(fd);
}
