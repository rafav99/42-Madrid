NAME = so_long

SRC = so_long.c render_m.c valid_path.c render_c.c movechar.c get_next_line.c\
		 valid_map.c get_next_line_utils.c directions.c\
		 ft_printf/printf_hex.c ft_printf/printf_put.c\
		 ft_printf/printf_write.c ft_printf/ft_printf.c
OBJS = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -L /usr/local/lib -lmlx -framework OpenGl -framework Appkit -D BUFFER_SIZE=5

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I /usr/local/include $(OBJS) -o $(NAME) $(LDFLAGS)

clean:	
		rm -f $(OBJS) 

fclean: clean
		rm -f  $(NAME)

re: fclean all

.PHONY: all clean fclean re 