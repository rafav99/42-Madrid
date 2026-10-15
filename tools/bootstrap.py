#!/usr/bin/env python3
# Import original 42 source files, pinned to verified commits.
# Preserve original files and adapt integrated builds without changing GitHub originals.
import os
import re
import shutil
import subprocess
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SOURCES = {
    "libft": ("Libft", "0695a86c1509cd885e969aa36910cde4df3b7cd5"),
    "ft_printf": ("ft_printf", "92125638ac8c3f6bd308d3cc8109f5cd9e920ac5"),
    "get_next_line": ("get_next_line", "d1d6d177185e343066c0b0cd00205f0630d9f4a9"),
    "so_long": ("so_long", "7d98688b578c0efcfb2e74edef23158e5424b23d"),
}

def exec_cmd(*args, cwd=None):
    subprocess.run(args, cwd=cwd, check=True)

def orig_fetch(project, original, commit):
    target = ROOT / project
    target.mkdir(parents=True, exist_ok=True)
    print("Importing", project, "from rafav99/" + original, flush=True)
    with tempfile.TemporaryDirectory() as temp:
        directory = Path(temp) / "repo"
        exec_cmd("git", "clone", "-q", "https://github.com/rafav99/" + original + ".git", str(directory))
        exec_cmd("git", "checkout", "-q", commit, cwd=directory)
        for item in directory.iterdir():
            if item.name == ".git":
                continue
            to = target / item.name
            if item.is_dir():
                if to.exists():
                    shutil.rmtree(to)
                shutil.copytree(item, to)
            else:
                to.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(item, to)
    (target / ".imported-commit").write_text(commit + "\n")

def replace_function(source, name):
    found = re.search(r"\b"+re.escape(name)+r"\s*\([^;]*?\)\s*\{", source, re.S)
    if not found:
        raise RuntimeError("Unable to locate source function: " + name)
    start = source.rfind("\n", 0, found.start()) + 1
    depth = 1
    idx = found.end()
    while idx < len(source) and depth:
        if source[idx] == "{":
            depth += 1
        if source[idx] == "}":
            depth -= 1
        idx += 1
    if depth:
        raise RuntimeError("Mismatched braces at " + name)
    return source[:start] + source[idx:]

def change_libft():
    d = ROOT / 'libft'
    (d/'Makefile').write_text('''NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = $(wildcard ft_*.c)
OBJS = $(SRCS:.c=.o)
all: $(NAME)
$(NAME): $(OBJS)
	ar rcs $@ $(OBJS)
%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
''')
    # Keep the author's arithmetic while dropping a historical unused local
    # that otherwise fails modern -Werror builds.
    itoa = d / 'ft_itoa.c'
    if itoa.exists():
        code = itoa.read_text()
        code = re.sub(r'^\s*long\s+rest;\s*\n', '', code, count=1, flags=re.M)
        code = re.sub(r'^\s*rest\s*=\s*1;\s*\n', '', code, count=1, flags=re.M)
        code = re.sub(r'^\s*rest\s*=\s*n\s*%\s*10;\s*\n', '', code, count=1, flags=re.M)
        itoa.write_text(code)
    for name in ('ft_isspace.c','ft_strcmp.c'):
        shutil.copy2(ROOT/'integration/extras'/name, d/name)
    header = d/'libft.h'
    content = header.read_text()
    content = content.replace('#endif', 'int ft_isspace(int c);\nint ft_strcmp(const char *a, const char *b);\n#endif')
    header.write_text(content)

def change_printf():
    d=ROOT/'ft_printf'
    obj=d/'printf_put.c'
    obj.write_text(replace_function(obj.read_text(), 'ft_strlen'))
    for name in ('ft_vsprintf.c','ft_dprintf.c'):
        shutil.copy2(ROOT/'integration/extras'/name, d/name)
    header=d/'ft_printf.h'
    s=header.read_text().replace('#endif', 'char *ft_vsprintf(const char *format, va_list args);\nint ft_dprintf(int fd, const char *format, ...);\n#endif')
    header.write_text(s)
    (d/'Makefile').write_text('''NAME = libftprintf.a
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
''')

def change_gnl():
    d=ROOT/'get_next_line'
    originals=d/'original'
    originals.mkdir(exist_ok=True)
    for p in list(d.iterdir()):
        if p.name.startswith('get_next_line') and p.suffix in ('.c','.h'):
            shutil.move(str(p),str(originals/p.name))
    shutil.copy2(ROOT/'integration/extras/get_next_line_integrated.c',d/'get_next_line.c')
    shutil.copy2(ROOT/'integration/extras/get_next_line_integrated.h',d/'get_next_line.h')
    (d/'Makefile').write_text('''NAME = libgnl.a
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
''')

def change_solong():
    d=ROOT/'so_long'
    (d/'original_dependencies').mkdir(exist_ok=True)
    for name in ('get_next_line.c','get_next_line_utils.c'):
        shutil.move(str(d/name),str(d/'original_dependencies'/name))
    shutil.move(str(d/'ft_printf'),str(d/'original_dependencies'/'ft_printf'))
    # Preserve the original Makefile as reference.
    shutil.move(str(d/'Makefile'),str(d/'original_dependencies'/'Makefile.mac-original'))
    # All code links to the canonical shared libraries.
    for file in d.glob('*.c'):
        contents=file.read_text()
        if file.name == 'so_long.c':
            contents=re.sub(r'int\s+readmap\s*\(char\s*\*map,\s*int\s+nrows,\s*int\s+fd,\s*char\s*\*a\)\s*\{.*?\n\}\n', '''static char *append_map(char *map, const char *line)
{
    char *combined;
    if (!map)
        return (ft_strdup(line));
    combined = ft_strjoin(map, line);
    free(map);
    return (combined);
}

int readmap(char *map, int nrows, int fd, char *a)
{
    int len;
    char *next;

    if (!a)
        return (1);
    len = (int)ft_strlen(a);
    while (a)
    {
        next = append_map(map, a);
        free(a);
        if (!next)
        {
            free(map);
            close(fd);
            return (1);
        }
        map = next;
        nrows++;
        a = get_next_line(fd);
    }
    close(fd);
    all_letters(map);
    valid_map(map, nrows);
    render(map, nrows, len);
    free(map);
    return (0);
}
''',contents,flags=re.S)
        if file.name == 'valid_path.c':
            contents=contents.replace('auxmap = malloc(ft_strlen(map));','auxmap = malloc(ft_strlen(map) + 1);')
        if file.name == 'movechar.c':
            contents=contents.replace('finished = 0;','''finished = 0;
#ifdef __linux__
    if (key == 97 || key == 65361) key = 0;
    else if (key == 100 || key == 65363) key = 2;
    else if (key == 119 || key == 65362) key = 13;
    else if (key == 115 || key == 65364) key = 1;
    else if (key == 65307) key = 53;
#endif''')
        file.write_text(contents)
    header=d/'so_long.h'
    contents=header.read_text().replace('# include <mlx.h>','# include <mlx.h>\n# include "../libft/libft.h"\n# include "../get_next_line/get_next_line.h"')
    contents=re.sub(r'^char\s+\*ft_strjoin\([^;]+;\s*$', '', contents, flags=re.M)
    header.write_text(contents)
    (d/'Makefile').write_text('''NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I.. -I../libft -I../get_next_line -I../ft_printf
UNAME := $(shell uname -s)
SRCS = so_long.c directions.c movechar.c render_c.c render_m.c valid_map.c valid_path.c
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
''')

    shutil.copy2(ROOT/'integration/extras/linux_render.c', d/'linux_render.c')
    make = (d/'Makefile').read_text()
    original_src = 'SRCS = so_long.c directions.c movechar.c render_c.c render_m.c valid_map.c valid_path.c'
    replacement_src = ('ifeq ($(UNAME),Darwin)\n' + original_src + '\nelse\n'
                       + 'SRCS = so_long.c valid_map.c valid_path.c linux_render.c\nendif')
    make = make.replace(original_src, replacement_src, 1)
    (d/'Makefile').write_text('.DEFAULT_GOAL := all\n' + make)

def update_all():
    # Existing shell calls ft_dprintf; the historical ft_printf.h now declares it.
    # Ensure shared strings do not accidentally duplicate the original libft.
    pass

def main():
    if (ROOT/'.integration-ready').exists():
        print('Original sources already imported; nothing to download.')
        return
    for key,(name,sha) in SOURCES.items():
        orig_fetch(key,name,sha)
    change_libft()
    change_printf()
    change_gnl()
    change_solong()
    update_all()
    (ROOT/'.integration-ready').write_text('Imported pinned original sources; integrated build configuration applied.\n')
    print('All original sources integrated. Build with: make -C <project>')

if __name__=='__main__':
    main()
