#include "main.h"

/**
 * execute_command - a function that executes a command
 *
 * @command: a NULL terminated pointer of command tokens
 * @sh: shell variable, allows for shell control
 * @errs: number of errors that occurred
 * @av: argument variable.
 */
void execute_command(char **command, int *sh, int *errs, char **av, int *exit_code)
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
      *exit_code = 0;
      free_command(command);
      return;
    }
  isexe = isexef(&command[0]);
  if (isexe == 0)
    {
      (*errs)++;
      fprintf(stderr, "%s: %d: %s: not found\n", av[0], *errs, command[0]);
      *exit_code = 127;
      free_command(command);
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
    }
    free_command(command);
  }
  else
  {
    wait(&status);
    if (WIFEXITED(status))
      {
	*exit_code = WEXITSTATUS(status);
      }
    else if (WIFSIGNALED(status))
      {
	fprintf(stderr, "Child process killed by signal: %d\n", WTERMSIG(status));
	*exit_code = WTERMSIG(status);
      }
    free_command(command);
  }

}
