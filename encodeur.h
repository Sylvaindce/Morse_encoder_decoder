#ifndef ENCODEUR_H_
# define ENCODEUR_H_

typedef struct	s_flag
{
  char		car;
  char		*morse;
}		t_flag;

int		my_putstr(char *str);
int		my_strcmp(char *s1, char *s2);
int		my_strlen(char *str);
int		make_error(char *str);
int		find_error(char *ret);
char		*get_next_line(const int fd);

#endif /* !ENCODEUR_H_ */
