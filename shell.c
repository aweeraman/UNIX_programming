#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

#define ARG_MAX 80

int main(int argc, char **argv) {
  char cmd[ARG_MAX];
  char *tok;
  int  num_tokens = 0;
  int  pid;
  int  status;

  do {
    printf("(%d) $ ", getpid());

    if (fgets(cmd, ARG_MAX, stdin) == NULL)
      break;

    if (cmd[strlen(cmd) - 1] == '\n')
      cmd[strlen(cmd) - 1] = '\0';

    if (strncmp(cmd, "", ARG_MAX) == 0)
      continue;

    char **cmd_args = calloc(0, 0);
    tok = strtok(cmd, " ");
    while (tok != NULL) {
      cmd_args = realloc(cmd_args, sizeof(char *) * ++num_tokens);

      if (cmd_args == NULL) {
        fprintf(stderr, "Memory allocation error while passing command!\n");
	exit(1);
      }

      cmd_args[num_tokens - 1] = tok;
      tok = strtok(NULL, " ");
    };

    cmd_args = realloc(cmd_args, sizeof(char *) * ++num_tokens);
    cmd_args[num_tokens - 1] = 0;

    if ((pid = fork()) < 0) {
      fprintf(stderr, "Fork error!\n");
    } else if (pid == 0) {
      execvp(cmd_args[0], cmd_args);
      fprintf(stderr, "%s: command not found\n", cmd);
      exit(1);
    }

    if ((pid = waitpid(pid, &status, 0)) < 0)
      fprintf(stderr, "Error waiting on child process: %d\n", pid);

    num_tokens = 0;
    free(cmd_args);

  } while (1);
}
