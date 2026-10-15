# 42 Madrid

**C · Unix systems · Algorithms · Concurrency · Graphics**

A collection of C projects developed during my time at **42 Madrid**. From low-level libraries to an interactive shell and a graphical game, these projects explore algorithms, memory management, processes, threads, and graphics programming.

## Projects

### [Minishell](minishell/)
**A Unix shell written in C.**

Tokenization, quotes and environment expansion; command execution with `fork`, `execve` and `waitpid`; pipes and redirections; interactive command history with GNU Readline.

**Built-ins:** `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

[Source and details →](minishell/README.md)

### [so_long](so_long/)
**A 2D exploration game using MiniLibX.**

Explore a library, collect the books and find the exit. Features tile-based maps, reachability validation, keyboard controls and XPM artwork. The Linux renderer composites sprites with transparency and uses an off-screen framebuffer for flicker-free movement.

[Source and details →](so_long/README.md)

### [Philosophers](philosophers/)
**Concurrency and synchronization with POSIX threads.**

A simulation of the dining philosophers problem using `pthread` and mutexes, with starvation monitoring, resource synchronization and clean termination.

[Source and details →](philosophers/README.md)

### [push_swap](push_swap/)
**Sorting integers with two stacks and a restricted instruction set.**

Argument parsing, index normalization, stack operations and chunk-based sorting. Includes randomized tests of operation counts and correctness. The implementation was rebuilt from earlier experimental drafts retained in the project.

[Source and details →](push_swap/README.md)

### [pipex](pipex/)
**Unix pipelines, process creation and file-descriptor redirection.**

A command pipeline in C using `pipe`, `fork`, `dup2` and `execve`, with input/output files and command lookup through `PATH`.

[Source and details →](pipex/README.md)

## C libraries

| Library | Focus |
| --- | --- |
| [libft](libft/) | String and memory operations, conversions, linked lists |
| [ft_printf](ft_printf/) | Variadic formatted output and file-descriptor formatting |
| [get_next_line](get_next_line/) | Buffered, line-by-line input with per-file-descriptor state |

These libraries are shared between the applications, avoiding duplicate implementations of common utilities.

## Build & test

On Ubuntu / Debian:

```bash
sudo apt install build-essential git python3 libreadline-dev libx11-dev libxext-dev libbsd-dev zlib1g-dev
make
make test
```

Build an individual project with `make -C <directory>`, for example `make -C push_swap`. The graphical game requires MiniLibX and an X11-compatible session; the first graphics build retrieves MiniLibX automatically.

```bash
./minishell/minishell
./philosophers/philo 5 800 200 200 5
./push_swap/push_swap 3 2 1
./pipex/pipex pipex/infile "grep naranja" "wc -l" /tmp/pipex-out.txt
(cd so_long && ./so_long maps/mymap.ber)
```

Each project directory contains its own documentation and source code.
