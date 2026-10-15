NAME = libgnl.a
CC = cc
BUFFER_SIZE ?= 42
CFLAGS = -Wall -Wextra -Werror -I../libft -DBUFFER_SIZE=$(BUFFER_SIZE)
all: $(NAME)
$(NAME): get_next_line.o
	ar rcs $@ $^
get_next_line.o: get_next_line.c get_next_line.h ../libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f get_next_line.o
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
