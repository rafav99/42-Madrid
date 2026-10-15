NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
LIBFT = ../libft/libft.a
SRC = src/main.c src/parse.c src/normalize.c src/operations.c src/sort.c
OBJ = $(SRC:.c=.o)
all: $(NAME)
$(LIBFT):
	$(MAKE) -C ../libft
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
src/%.o: src/%.c include/push_swap.h
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@
clean:
	rm -f $(OBJ) $(OBJ:.o=.d)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re

-include $(OBJ:.o=.d)
