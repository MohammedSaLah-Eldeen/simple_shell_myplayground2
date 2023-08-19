#include "main.h"

/**
 * penvf - prints the environment variables
 *
 */
void penvf(void)
{
  int e = 0;
  for (; environ[e] != NULL; e++)
    printf("%s\n", environ[e]);
}
