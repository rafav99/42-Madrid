NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -std=c11 -pthread
SRC = philosophers.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

test: $(NAME)
	python3 tests/test_philosophers.py

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all test clean fclean re
