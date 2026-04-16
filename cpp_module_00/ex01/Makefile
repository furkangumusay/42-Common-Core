NAME    = phonebook
CC 	    = c++
CFLAGS  = -Wall -Wextra -Werror -std=c++98
RM      = rm -rf 

SRC     = main.cpp Contact.cpp PhoneBook.cpp
OBJ     = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONEY: all clean fclean re