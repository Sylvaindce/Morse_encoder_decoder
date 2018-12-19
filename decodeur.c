#include <stdlib.h>
#include <unistd.h>
#include "encodeur.h"

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

static int	decode(char *ret)
{
  int		i;
  int		k;
  int		j;
  char		*tmp;

  i = 0;
  if ((tmp = malloc(my_strlen(ret))) == NULL || find_error(ret) == -1)
    return (-1);
  while (ret[i] != '\0')
    {
      k = 0;
      j = 0;
      while (tmp[j] != '\0')
	tmp[j++] = '\0';
      j = 0;
      while (ret[i] != '*' && ret[i] != '\0' && ret[i] != ' ')
	tmp[k++] = ret[i++];
      while (my_strcmp(tmp, flags[j].morse) != 0 && flags[j].morse != NULL)
  	j++;
      write(1, &flags[j].car, 1);
      if (ret[i] == ' ')
	write(1, " ", 1);
      i++;
    }
}

static char	replace(int count_point, char *str, int *i)
{
  if (count_point == 3)
    {
      (*i)--;
      return ('*');
    }
  else if (count_point == 7)
    {
      (*i)--;
      return (' ');
    }
  else if (count_point == 1)
    return ('.');
  return (str[*i]);
}

static char	*my_parser(char *str)
{
  int		count_point;
  int		i;
  int		k;
  char		*ret;

  i = 0;
  k = 0;
  if ((ret = malloc(my_strlen(str))) == NULL)
    return (NULL);
  while (str[i] != '\0')
    {
      count_point = 0;
      while (str[i] == '.')
	{
	  count_point++;
	  i++;
	}
      ret[k++] = replace(count_point, str, &i);
      if (count_point == 1)
      	ret[k++] = str[i];
      i++;
    }
  return (ret);
}

int		main()
{
  char		*str;
  int		i;

  i = 0;
  while ((str = get_next_line(0)) != NULL && my_strcmp(str, "exit") != 0)
    {
      str = my_parser(str);
      if (decode(str) == -1)
	return (-1);
      my_putstr("\n");
    }
}
