#include <stdlib.h>
#include <unistd.h>
#include "encodeur.h"

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    i++;
  return (i);
}

int	my_putstr(char *str)
{
  write(1, str, my_strlen(str));
}

int	my_strcmp(char *s1, char *s2)
{
  int	compt;
  int	result;

  result = 0;
  compt = 0;
  if (s1 == NULL || s2 == NULL)
    return (-1);
  while (s1[compt] == s2[compt] && (s1[compt] != '\0' || s2[compt] != '\0'))
    compt = compt + 1;
  if (s1[compt] == s2[compt])
      return (0);
  return (-1);
}

int	my_putstr_error(char *str)
{
  write(2, str, my_strlen(str));
}
