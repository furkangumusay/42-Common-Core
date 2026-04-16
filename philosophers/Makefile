NAME	= philo
CC		= cc
RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror

SRC =	main.c \
		utils.c \
		setup_sim.c \
		cleanup.c \
		philo_actions.c \
		init_resources.c \
		philo_monitoring.c \

OBJ_DIR = .objs

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re
