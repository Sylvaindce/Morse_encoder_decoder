#include <stdlib.h>
#include <unistd.h>
#include "encodeur.h"
#include "fonctions.h"

static const t_flag	flags[]=
  {
    {'0', "_._._._._"}, {'1', "-._._._._"}, {'2', "-.-._._._"},
    {'3', "-.-.-._._"}, {'4', "-.-.-.-._"}, {'5', "-.-.-.-.-"},
    {'6', "_.-.-.-.-"}, {'7', "_._.-.-.-"}, {'8', "_._._.-.-"},
    {'9', "_._._._.-"}, {'a', "-._"}, {'b', "_.-.-.-"},
    {'c', "_.-._.-"}, {'d', "_.-.-"}, {'e', "-"},
    {'f', "-.-._.-"}, {'g', "_._.-"}, {'h', "-.-.-.-"},
    {'i', "-.-"}, {'j', "-._._._"}, {'k', "_.-._"},
    {'l', "-._.-.-"}, {'m', "_._"}, {'n', "_.-"},
    {'o', "_._._"}, {'p', "-._._.-"}, {'q', "_._.-._"},
    {'r', "-._.-"}, {'s', "-.-.-"}, {'t', "_"},
    {'u', "-.-._"}, {'v', "-.-.-._"}, {'w', "-._._"},
    {'x', "_.-.-._"}, {'y', "_.-._._"}, {'z', "_._.-.-"},
    {' ', "......."}, {'.', "-._-._.-._"}, {',', "_._.-.-._._"},
    {'?', "-.-._._.-.-"}, {'!', "_.-._.-._._"}, {';', "_.-._.-._.-"},
    {'/', "_.-.-._.-"}, {'+', "-._.-._.-"}, {'\'', "-._._._._.-"},
    {'-', "_.-.-.-.-._"}, {'=', "_.-.-.-._"}, {'(', "_.-._._.-"},
    {')', "_.-._._.-._"}, {'_', "-.-._._.-._"}, {'$', "-.-.-._.-.-._"},
    {'\"', "-._.-.-._.-"}, {'@', "-._._.-._.-"}, {'&', "-._.-.-.-"}
  };

int		make_error(char *str)
{
  int		i;
  int		k;

  i = 0;
  while (str[i] != '\0')
    {
      k = 0;
      while (str[i] != flags[k].car && k < 54)
	k++;
      if (k == 54 && str[i] != '&')
	{
	  my_putstr_error("Bad charactere : \'");
	  write(2, &str[i], 1);
	  my_putstr_error("\'\n");
	  return (-1);
	}
      i++;
    }
  return (0);
}

static char	*my_clean(char *tmp)
{
  int		j;

  j = 0;
  while (tmp[j] != '\0')
    tmp[j++] = '\0';
  return (tmp);
}

int		my_error(int j, char *str)
{
  if (j == 54)
    {
      my_putstr_error("Bad charactere : \'");
      my_putstr_error(str);
      my_putstr_error("\'\n");
      return (-1);
    }
  return (0);
}

int		find_error(char *ret)
{
  int		i;
  int		k;
  int		j;
  char		 *tmp;

  i = 0;
  if ((tmp = malloc(my_strlen(ret))) == NULL)
    return (-1);
  while (ret[i] != '\0')
    {
      k = 0;
      tmp = my_clean(tmp);
      j = 0;
      while (ret[i] != '*' && ret[i] != '\0' && ret[i] != ' ')
	tmp[k++] = ret[i++];
      while (j < 54 && my_strcmp(tmp, flags[j].morse) != 0)
  	j++;
      if (my_error(j, tmp) == -1)
	return (-1);
      i++;
    }
  return (0);
}
