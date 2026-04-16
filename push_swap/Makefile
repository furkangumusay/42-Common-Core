NAME = push_swap

SRC = cleanup_errors.c	 \
	  selection_sort.c  \
	  push_swap.c      \
	  radix_sort.c    \
	  rule_a.c       \
	  rule_b.c      \
	  utils.c      \

OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT)

$(LIBFT):
		$(MAKE) -C libft

clean:
		$(MAKE) -C libft clean
		rm -f $(OBJ)
fclean: clean
		$(MAKE) -C libft fclean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
