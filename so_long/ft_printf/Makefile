NAME		=	libftprintf.a
SRC			=	ft_printf.c ft_printf.utils.c
OBJ			=	$(SRC:.c=.o)
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf
AR			=	ar rc

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(FLAGS) -c $(SRC)
	$(AR) $(NAME) $(OBJ)
			
clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re