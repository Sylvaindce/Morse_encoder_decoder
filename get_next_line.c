#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static char	*my_malloc()
{
  char		*str;
  int		i;

  i = 0;
  if ((str = malloc((BUFFER_READ + 1) * sizeof(char))) == NULL)
      return (NULL);
  while (str[i] != '\0')
    str[i] = '\0';
  return (str);
}

static int	end_str(t_data *data)
{
  int		stop;

  stop = 0;
  if (data->buffer[data->i] == '\n')
    {
      stop = 1;
      data->i = data->i + 1;
    }
  if (data->buffer[data->i] == '\0')
    data->nop = 0;
  return (stop);
}

static char	*init_var(t_data *data, int fd)
{
  if (data->i == data->k)
    {
      data->i = 0;
      data->k = 0;
    }
  if (data->k == 0)
    if ((data->k = read(fd, data->buffer, BUFFER_READ)) <= 0
	|| data->buffer[0] == '\0')
      return (NULL);
}

char		*get_next_line(const int fd)
{
  static t_data	data;
  char		*str;
  int		j;
  int		stop;

  j = 0;
  stop = 0;
  if (BUFFER_READ <= 0 || (str = my_malloc()) == NULL)
    return (NULL);
  while (stop == 0)
    {
      if (data.nop == 0)
      	{
	  data.nop = 1;
	  if ((data.buffer = my_malloc()) == NULL)
	    return (NULL);
	}
      if ((init_var(&data, fd)) == NULL)
	return (NULL);
      while (data.i < data.k && data.buffer[data.i] != '\n')
	str[j++] = data.buffer[data.i++];
      stop = end_str(&data);
    }
  return (str);
}
