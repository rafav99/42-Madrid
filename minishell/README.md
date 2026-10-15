# Minishell

An interactive **Unix shell in C**, covering parsing, process execution and file-descriptor management.

### Features

- Tokenization, quoting, environment expansion and `$?`
- External programs through `PATH`, `fork`, `execve` and `waitpid`
- Pipes and standard input/output redirection (`<`, `>`, `>>`)
- Built-ins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- GNU Readline command history and basic signal handling

### Structure

- `src/parser/` — tokenization and expansions
- `src/executor/` — pipelines, process execution and redirections
- `src/builtins/` — internal commands
- `src/env/` and `src/signals/` — environment and signal handling

```bash
make -C libft
make -C ft_printf
make -C minishell
./minishell/minishell
```

**Known limitation:** heredocs (`<<`) are not fully implemented.

**Focus:** Unix processes, pipes, parsing, signals and memory ownership.
