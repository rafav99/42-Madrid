NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -I../libft -I../ft_printf
SRCS = pipex.c pipexec.c
OBJS = $(SRCS:.c=.o)
LIBS = ../ft_printf/libftprintf.a ../libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

../libft/libft.a:
	$(MAKE) -C ../libft

../ft_printf/libftprintf.a:
	$(MAKE) -C ../ft_printf

%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
