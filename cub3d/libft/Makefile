# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/24 11:08:49 by fgumusay          #+#    #+#              #
#    Updated: 2023/12/24 11:09:33 by fgumusay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
AR = ar rcs

SRC = ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memset.c ft_strlen.c \
	  ft_atoi.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_strchr.c ft_strdup.c ft_strjoin.c\
	  ft_strlcat.c ft_strlcpy.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c\
	  ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c\
	  

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "Compilation has been completed."

clean:
	@$(RM) $(OBJS)
	@echo "Object files cleaned."

fclean: clean
	@$(RM) $(NAME)
	@echo "All files have been deleted."

re: fclean all
	@echo "All files were deleted and compiled again."

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "The file with the $< extension was used to create a file with the $@ extension."

.PHONY: all fclean clean re