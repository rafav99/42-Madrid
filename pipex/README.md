# pipex

A Unix pipeline exercise implemented in C at **42 Madrid**.

The program connects commands using `pipe`, `fork`, `dup2` and `execve`, redirecting input from a file and output to another file. It also supports chains of more than two commands.

## Example

```bash
make -C libft
make -C ft_printf
make -C pipex
./pipex/pipex pipex/infile "grep naranja" "wc -l" /tmp/pipex-out.txt
```

This is equivalent in intent to `< infile grep naranja | wc -l > outfile`.

The project resolves external commands from `PATH` and relies on shared [libft](../libft/) and [ft_printf](../ft_printf/) rather than keeping another copy of their implementations.

**Focus:** processes, file descriptors, pipes, standard streams and command execution.

This is a basic pipeline implementation, not a complete shell parser.
