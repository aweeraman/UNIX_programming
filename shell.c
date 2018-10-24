#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

#define ARG_MAX      80
#define HOSTNAME_LEN 80
#define LOGIN_LEN    80

static char *pname;

void prompt() {
  char hn[HOSTNAME_LEN];
  char login[LOGIN_LEN];

  gethostname(hn, HOSTNAME_LEN);
  getlogin_r(login, LOGIN_LEN);

  printf("%s@%s %s ", login, hn, getuid() == 0 ? "#": "$");
}

char **get_cmd_args(char *cmd) {
  char *tok;
  int  num_tokens = 0;

  char **cmd_args = calloc(0, 0);
  tok = strtok(cmd, " ");

  while (tok != NULL) {
    cmd_args = realloc(cmd_args, sizeof(char *) * ++num_tokens);

    if (cmd_args == NULL) {
      perror(pname);
      exit(1);
    }

    cmd_args[num_tokens - 1] = tok;
    tok = strtok(NULL, " ");
  }

  cmd_args = realloc(cmd_args, sizeof(char *) * ++num_tokens);
  cmd_args[num_tokens - 1] = 0;

  return cmd_args;
}

int main(int argc, char **argv) {
  char cmd[ARG_MAX];
  int  pid;
  int  status;

  pname = argv[0];

  do {
    prompt();

    if (fgets(cmd, ARG_MAX, stdin) == NULL)
      break;

    if (cmd[strlen(cmd) - 1] == '\n')
      cmd[strlen(cmd) - 1] = '\0';

    char **cmd_args = get_cmd_args(cmd);

    if ((pid = fork()) < 0) {
      perror(pname);
    } else if (pid == 0) {
      execvp(cmd_args[0], cmd_args);
      perror(pname);
      exit(1);
    }

    if ((pid = waitpid(pid, &status, 0)) < 0)
      perror(pname);

    free(cmd_args);

  } while (1);
}
