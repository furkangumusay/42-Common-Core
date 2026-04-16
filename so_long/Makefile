NAME = so_long

CC = gcc
CFLAGS = -Wall -Wextra -Werror 
RM = rm -f

SRC = main.c      \
	  move.c       \
	  ft_free.c     \
	  map_read.c     \
	  setup_data.c    \
	  mlx_include.c    \
	  move_control.c    \
	  map_wall_control.c \

OBJ = $(SRC:.c=.o)
	  
FT_PRINTF_PATH = ./ft_printf
FT_PRINTF = $(FT_PRINTF_PATH)/libftprintf.a


MINILIBX_PATH = ./minilibx
MINILIBX = $(MINILIBX_PATH)/libmlx.a

MINILIBX_FLGS = -L$(MINILIBX_PATH) -lmlx -framework OpenGL -framework AppKit -L$(MINILIBX_PATH) -lmlx

all : $(NAME)

$(MINILIBX):
	make -C $(MINILIBX_PATH)

$(FT_PRINTF):
	make -C $(FT_PRINTF_PATH)

$(NAME): $(MINILIBX) $(FT_PRINTF) $(OBJ)
	$(CC) $(CFLAGS) $(FT_PRINTF) $(MINILIBX_FLGS)  $(OBJ) -o $(NAME)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	make -C $(FT_PRINTF_PATH) clean
	make -C $(MINILIBX_PATH) clean
	$(RM) $(OBJ)

fclean: clean
	make -C $(FT_PRINTF_PATH) fclean
	make -C $(MINILIBX_PATH) clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
