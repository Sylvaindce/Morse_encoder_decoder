
SRC1=		encodeur.c \
		get_next_line.c \
		fonctions.c \
		my_errors.c \

SRC2=		decodeur.c \
		get_next_line.c \
		fonctions.c \
		my_errors.c \

CC=		cc

RM=		rm -f

NAME1=		encodeur

NAME2=		décodeur

OBJ1=		$(SRC1:.c=.o)

OBJ2=		$(SRC2:.c=.o)

all:		$(NAME1) $(NAME2)

$(NAME1):	$(OBJ1)
		$(CC) -o $(NAME1) $(OBJ1)

$(NAME2):	$(OBJ2)
		$(CC) -o $(NAME2) $(OBJ2)

clean:
		$(RM) $(OBJ1)
		$(RM) $(OBJ2)

fclean:		clean
		$(RM) $(NAME1)
		$(RM) $(NAME2)

re:		fclean all

bueno:
		cat k_bueno

.PHONY: 	all clean fclean re bueno
