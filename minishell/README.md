# Minishell

A small interactive Unix shell written in C as a systems-programming project at **42 Madrid**.

## Overview

The implementation includes command tokenization and parsing, environment-variable expansion, process creation, pipelines, input/output redirection, and built-in commands. It uses GNU Readline for interactive input and command history.

### Implemented

- External commands found through `PATH`, using `fork`, `execve`, and `waitpid`
- Pipelines using `pipe` and `dup2`
- Input (`<`) and output (`>`, `>>`) redirections
- Single and double quotes for basic argument grouping
- Environment expansion, including `$?`
- Built-ins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`
- Basic terminal signal handling

## Requirements

A POSIX-like Unix environment, a C compiler, Make, and the GNU Readline development library.

On Ubuntu or Debian, install the build dependencies with:

```bash
sudo apt install build-essential libreadline-dev
```

## Build and run

```bash
make
./minishell
```

For example:

```console
minishell$ echo "Hello, world"
Hello, world
minishell$ pwd
/home/user
minishell$ echo hello | wc -c
6
minishell$ export MY_VAR=test
minishell$ echo $MY_VAR
test
minishell$ exit
```

Clean generated files with `make fclean`.

## Tests

After building, run the smoke-test suite:

```bash
python3 tests/test_smoke.py
```

The tests check simple commands, quoted arguments, pipelines, variable expansion, command-not-found status, and common syntax errors. They are not a substitute for a comprehensive shell conformance or memory-safety test suite.

## Known limitations

- **Here-documents (`<<`) are not implemented correctly.** The syntax is recognized, but the current redirection handler does not read and store text through the delimiter. Do not rely on heredocs in this version.
- This is a learning implementation, not a complete POSIX-compatible shell. Complex quoting, parameter expansion, and corner cases need additional verification.
- The repository has not yet been validated with Valgrind or a full interactive terminal test matrix.

## Structure

- `src/parser/` — lexical analysis, expansion, and command construction
- `src/executor/` — command execution, pipes, and redirections
- `src/builtins/` — shell built-in commands
- `src/env/` — environment storage and utilities
- `src/signals/` — signal handling
- `src/utils/` — shared helpers
- `include/` — headers

The existing source-file attribution headers have been preserved.
