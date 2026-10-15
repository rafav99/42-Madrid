# Nombre del ejecutable
NAME = minishell

# Compilación y sistema
CC = cc
CFLAGS = -Wall -Werror -Wextra 

# Comandos
RM = rm -f
MD = mkdir -p

# Directorios
SRC_DIR = src/
OBJ_DIR = obj/
DEP_DIR = dep/
INC_DIR = include/

# Inclusión de directorios
INCLUDE = -I$(INC_DIR) -I../libft -I../ft_printf

# Fuentes
SRCS = minishell.c \
       $(SRC_DIR)parser/parser.c \
       $(SRC_DIR)parser/tokenizer.c \
       $(SRC_DIR)parser/tokenizer_2.c \
       $(SRC_DIR)parser/expand_string.c \
       $(SRC_DIR)parser/expand_var.c \
       $(SRC_DIR)parser/expander_utils.c \
       $(SRC_DIR)parser/parser_2.c \
       $(SRC_DIR)parser/build_commands.c \
       $(SRC_DIR)parser/token_utils.c \
       $(SRC_DIR)executor/executor.c \
       $(SRC_DIR)executor/executor_2.c \
       $(SRC_DIR)executor/executor_3.c \
       $(SRC_DIR)executor/execute_pipeline.c \
       $(SRC_DIR)executor/pipeline_utils.c \
       $(SRC_DIR)executor/redirections.c \
       $(SRC_DIR)executor/redirections_2.c \
       $(SRC_DIR)executor/pipes.c \
       $(SRC_DIR)executor/paths.c \
       $(SRC_DIR)builtins/cd.c \
       $(SRC_DIR)builtins/echo.c \
       $(SRC_DIR)builtins/env.c \
       $(SRC_DIR)builtins/exit.c \
       $(SRC_DIR)builtins/export.c \
       $(SRC_DIR)builtins/pwd.c \
       $(SRC_DIR)builtins/unset.c \
       $(SRC_DIR)env/env_utils.c \
       $(SRC_DIR)env/env_utils_2.c \
       $(SRC_DIR)env/env_expand.c \
       $(SRC_DIR)env/env_init_append.c \
       $(SRC_DIR)env/env_var_sign.c \
       $(SRC_DIR)signals/signals.c \
       $(SRC_DIR)utils/ft_split_cmd.c \
       $(SRC_DIR)utils/memory_utils.c \
       $(SRC_DIR)utils/error_utils.c \
       $(SRC_DIR)utils/error_utils_2.c \
       $(SRC_DIR)utils/other_utils.c \

# Objetos y dependencias generadas durante compilación
OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)
DEPS = $(OBJS:.o=.d)

LIBS = ../ft_printf/libftprintf.a ../libft/libft.a -lreadline

$(OBJ_DIR)%.o: %.c
	@$(MD) $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -MMD -MP -c $< -o $@

# Reglas principales
all: $(NAME)

../libft/libft.a:
	$(MAKE) -C ../libft

../ft_printf/libftprintf.a:
	$(MAKE) -C ../ft_printf

$(NAME): $(OBJS) ../libft/libft.a ../ft_printf/libftprintf.a
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "\033[32m[OK] $(NAME) compilado correctamente.\033[0m"

# Limpieza
clean:
	@$(RM) -r $(OBJ_DIR) $(DEP_DIR)
	@echo "\033[31m[Limpiado] Objetos y dependencias eliminados.\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[31m[Limpiado] Ejecutable eliminado.\033[0m"

re:
	$(MAKE) fclean
	$(MAKE) all

# Ignorar archivos intermedios
.PHONY: all clean fclean re

# Incluir dependencias
-include $(DEPS)
