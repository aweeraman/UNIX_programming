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
    fprintf(stderr, "Error %d opening file: %s\n", errno, argv[1]);
  }

  while ((n = read(fd, buffer, BUFSIZE)) > 0) {
    if ((write(STDOUT, buffer, n)) != n) {
      fprintf(stderr, "Error while writing to standard output!");
    }
  }

  close(fd);
}
