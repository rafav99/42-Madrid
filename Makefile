.NOTPARALLEL:
.PHONY: all core test clean fclean re libft ft_printf get_next_line push_swap philosophers pipex minishell so_long

all: libft ft_printf get_next_line push_swap philosophers pipex minishell so_long
core: libft ft_printf get_next_line push_swap philosophers pipex minishell
libft:
	$(MAKE) -C libft
ft_printf: libft
	$(MAKE) -C ft_printf
get_next_line: libft
	$(MAKE) -C get_next_line
push_swap: libft
	$(MAKE) -C push_swap
pipex: libft ft_printf
	$(MAKE) -C pipex
philosophers:
	$(MAKE) -C philosophers
minishell: libft ft_printf
	$(MAKE) -C minishell
so_long: libft ft_printf get_next_line
	$(MAKE) -C so_long
clean:
	@for d in libft ft_printf get_next_line push_swap philosophers pipex minishell so_long; do $(MAKE) -C "$$d" clean || exit $$?; done
fclean: clean
	@for d in libft ft_printf get_next_line push_swap philosophers pipex minishell so_long; do $(MAKE) -C "$$d" fclean || exit $$?; done
re: fclean all
test: libft ft_printf get_next_line push_swap philosophers pipex
	python3 push_swap/tests.py
	$(MAKE) -C philosophers test
	python3 tests/test_gnl.py
