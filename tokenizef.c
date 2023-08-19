#include "main.h"

/**
 * tokenizef - tokenizes a string to its simple tokens.
 *
 * @line: string to be tokenized, delimiter is a space.
 * Return: an array pointers that consists of the command tokens.  
 */
char **tokenizef(char *line)
{
  char *token;
  char **command;
  int i = 0;

  if (line == NULL)
    return (NULL);
  
  token = strtok(line, " ");
  command = malloc(2 * sizeof(char *));

  while (token != NULL)
    {
      command = realloc(command, (i + 2) * sizeof(char *));
      command[i] = strdup(token);
      i++;
      token = strtok(NULL, " ");
    }

  command[i] = NULL;
  free(line);

  return (command);
}
