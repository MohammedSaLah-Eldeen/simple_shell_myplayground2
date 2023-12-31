#include "main.h"

/**
 * main - the main function
 *
 * @ac: number of args
 * @av: args passed
 * Return: 0 success.
 */


int main(int ac, char **av)
{
  int shell = 1;
  int errors = 0;
  char **command = NULL;
  int exit_code = 0;
  ac = ac;
  
  while (shell)
    {
      command = fetch_command(&shell);
      if (command != NULL)
	execute_command(command, &shell, &errors, av, &exit_code);
    }

  return (exit_code);
}
