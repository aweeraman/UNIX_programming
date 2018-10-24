#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>

int main(int argc, char **argv) {
  DIR           *dirp;
  struct dirent *dire;

  if (argc != 2) {
    fprintf(stderr, "Usage: ls directory_name\n");
    exit(1);
  }

  if ((dirp = opendir(argv[1])) == NULL) {
    perror(argv[0]);
    exit(2);
  }

  while ((dire = readdir(dirp)) != NULL) {
    printf("%s\n", dire->d_name);
  }
}
