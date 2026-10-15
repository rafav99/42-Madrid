NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I../libft
SRCS = ft_printf.c printf_hex.c printf_put.c printf_write.c ft_vsprintf.c ft_dprintf.c
OBJS = $(SRCS:.c=.o)
all: $(NAME)
$(NAME): $(OBJS)
	ar rcs $@ $(OBJS)
%.o: %.c ft_printf.h ../libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
