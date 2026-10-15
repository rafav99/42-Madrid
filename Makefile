# All external project sources are imported from the author's own GitHub repositories.
.NOTPARALLEL:
.PHONY: all setup libs core clean fclean re test libft ft_printf get_next_line push_swap philosophers minishell so_long

all: setup libft ft_printf get_next_line push_swap philosophers minishell so_long
setup:
	@python3 tools/bootstrap.py
libs: setup libft ft_printf get_next_line
core: setup libft ft_printf get_next_line push_swap philosophers minishell
libft: setup
	$(MAKE) -C libft
ft_printf: libft
	$(MAKE) -C ft_printf
get_next_line: libft
	$(MAKE) -C get_next_line
push_swap: libft
	$(MAKE) -C push_swap
philosophers:
	$(MAKE) -C philosophers
minishell: libft ft_printf
	$(MAKE) -C minishell
so_long: libft ft_printf get_next_line
	$(MAKE) -C so_long
clean:
	@for d in libft ft_printf get_next_line push_swap philosophers minishell so_long; do if test -f "$$d/Makefile"; then $(MAKE) -C "$$d" clean || exit $$?; fi; done
fclean: clean
	@for d in libft ft_printf get_next_line push_swap philosophers minishell so_long; do if test -f "$$d/Makefile"; then $(MAKE) -C "$$d" fclean || exit $$?; fi; done
re: fclean all
test: setup libft ft_printf get_next_line push_swap philosophers
	python3 push_swap/tests.py
	$(MAKE) -C philosophers test
	python3 integration/tests/test_gnl.py
