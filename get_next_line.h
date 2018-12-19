#ifndef	GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

#define	BUFFER_READ (50000)

char		*get_next_line(const int fd);

typedef struct	s_data
{
  int		i;
  int		k;
  int		nop;
  char		*buffer;
}		t_data;

#endif /* !GET_NEXT_LINE_H_ */
