#include "main.h"

/**
 * execute_command - a function that executes a command
 *
 * @command: a NULL terminated pointer of command tokens
 * @sh: shell variable, allows for shell control
 * @errs: number of errors that occurred
 * @av: argument variable.
 */
void execute_command(char **command, int *sh, int *errs, char **av)
{
  pid_t pid;
  int status;
  int isexe;

  if (strcmp(command[0], "exit") == 0)
    {
      free_command(command);
      *sh = 0;
      return;
    }
  if (strcmp(command[0], "env") == 0)
    {
      penvf();
      free_command(command);
      return;
    }
  isexe = isexef(&command[0]);
  if (isexe == 0)
    {
      (*errs)++;
      fprintf(stderr, "%s: %d: %s: not found\n", av[0], *errs, command[0]);
      execve(command[0], command, environ);
      return;
    }
  else if (isexe == 1)
      findpathf(&command[0]);

  pid = fork();
  if (pid == -1)
  {
    perror("Fork failed");
    return;
  }
  else if (pid == 0)
  {
    if (execve(command[0], command, environ) == -1)
    {
      (*errs)++;
      perror("Execve failed");
      free_command(command);
      exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
  }
  else
  {
    wait(&status);
  }

}