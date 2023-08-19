#include "main.h"

/**
 * isexef - determines if a command name is executable or in path or not.
 *
 * @cmdname: pointer to the first token of the command.
 * Return: 0 if not executable,
 * 1 if executable is found in path,
 * 2 if full executable pathname was passed.
 */
int isexef(char **cmdname)
{
  char *path = getenv("PATH");
  char *pathcp = strdup(path);
  char *token = strtok(pathcp, ":");
  char *trypath = NULL;
  
  if (access(*cmdname, X_OK) == 0)
    {
      free(pathcp);
      return (2);
    }

  while (token != NULL)
    {
      trypath = malloc(strlen(*cmdname) + strlen(token) + 2);
      sprintf(trypath, "%s/%s", token, *cmdname);

      if (access(trypath, X_OK) == 0)
	{
	  free(pathcp);
	  free(trypath);
	  return (1);	  
	}
      free(trypath);
      token = strtok(NULL, ":");
    }

  free(pathcp);
  return (0);
}
