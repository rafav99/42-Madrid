.DEFAULT_GOAL := all
NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I.. -I../libft -I../get_next_line -I../ft_printf
UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
SRCS = so_long.c directions.c movechar.c render_c.c render_m.c valid_map.c valid_path.c
else
SRCS = so_long.c valid_map.c valid_path.c linux_render.c
endif
OBJS = $(SRCS:.c=.o)
ifeq ($(UNAME),Darwin)
MLX_LIB = /usr/local/lib/libmlx.a
MLX_FLAGS = -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit
CFLAGS += -I/usr/local/include
else
MLX_DIR = ../third_party/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
CFLAGS += -I$(MLX_DIR)
$(MLX_LIB):
	@mkdir -p ../third_party
	@if [ ! -d $(MLX_DIR) ]; then git clone -q https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); fi
	$(MAKE) -C $(MLX_DIR)
endif
all: $(NAME)
$(NAME): $(OBJS) $(MLX_LIB) ../get_next_line/libgnl.a ../ft_printf/libftprintf.a ../libft/libft.a
	$(CC) $(OBJS) $(MLX_FLAGS) ../get_next_line/libgnl.a ../ft_printf/libftprintf.a ../libft/libft.a -o $@
%.o: %.c so_long.h | $(MLX_LIB)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
