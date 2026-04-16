NAME	= cub3D

CC		= cc

RM		= rm -rf

CFLAGS	= -Wall -Wextra -Werror -g

SRC =   game_loop/gameloop.c \
        game_loop/raycasting_render.c \
        game_loop/raycasting.c \
        game_loop/wall_texture.c \
		garbage_collection/exit.c \
        garbage_collection/safe_malloc.c \
        garbage_collection/memory_manage.c \
        init/init.c \
        map_funcs/map_check.c \
        map_funcs/map_parser.c \
        map_funcs/utils.c \
		map_funcs/map_integrity_check.c \
		map_funcs/map_control_utils.c \
		map_funcs/map_building.c \
		map_funcs/map_utils.c \
		map_funcs/map_handling.c \
        main.c

LIBFT	= libft/libft.a
MLX		= minilibx/libmlx.a
MLXFLAG = -lXext -lX11 -lm -lz
 
OBJ_DIR = .objs

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all : $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(MLX) $(MLXFLAG)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	@echo -e "\033[2J\033[H"
	@echo "\033[1;32mCompiling : \033[1;34m$<\033[0m"
	@sleep 0.01
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C libft

$(MLX):
	@$(MAKE) -C minilibx

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C libft clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean
	@$(MAKE) -C minilibx clean

re: fclean all

.PHONY: all fclean clean re
