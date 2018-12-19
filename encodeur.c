#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
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

static void	choose_beep(char c)
{
  if (c == '-')
    {
      /*printf("\a");*/
      write(1, "\a", 1);
      usleep(20);
    }
  else if (c == '_')
    {
      printf("\a");
      /*write(1, "\a", 1);*/
      usleep(70);
    }
  /*else if (c == '.')
    usleep(90000);*/
}

static char	*str_to_minus(char *str)
{
  int		i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] >= 'A' && str[i] <= 'Z')
	str[i] = str[i] + 32;
      i++;
    }
  return (str);
}

static void	write_message(int k, int ac, char **av)
{
  int		i;

  i = 0;
  if (flags[k].car == ' ')
    my_putstr("\033[1;31m");
  if (ac == 2 && my_strcmp(av[1], "-s") == 0)
    {
      while (flags[k].morse[i] != '\0')
	{
	  choose_beep(flags[k].morse[i]);
	  write(1, &flags[k].morse[i], 1);
	  i++;
	}
    }
  else
    my_putstr(flags[k].morse);
  my_putstr("\033[0;0m");
}

int		main(int ac, char **av)
{
  char		*str;
  int		i;
  int		k;

  while ((str = get_next_line(0)) != NULL && my_strcmp(str, "exit") != 0)
    {
      i = 0;
      str = str_to_minus(str);
      if (make_error(str) == -1)
	return (-1);
      while (str[i] != '\0')
	{
	  k = 0;
	  while (str[i] != flags[k].car && k < 54)
	    k++;
	  write_message(k, ac, av);
	  my_putstr("\033[1;32m");
	  if (str[i + 1] != '\0' && str[i + 1 ] != ' ' && str[i] != ' ')
	    my_putstr("...");
	  my_putstr("\033[0;0m");
	  i++;
	}
      my_putstr("\n");
    }
  return (0);
}
