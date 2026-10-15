# 42 Madrid — C projects

A single workspace consolidating projects completed at **42 Madrid**, integrating the author's original repositories and the recovered local projects into one reusable C codebase.

## Contents

| Project | Origin | Integration |
| --- | --- | --- |
| `libft` | [Original Libft](https://github.com/rafav99/Libft) (2021) | Canonical collection of general-purpose C functions. `ft_strcmp` and `ft_isspace` are added as small shared extensions. |
| `ft_printf` | [Original ft_printf](https://github.com/rafav99/ft_printf) (2021) | Shared formatter. Original source plus `ft_dprintf`/`ft_vsprintf` extracted from the recovered minishell code. `ft_strlen` is provided solely by libft. |
| `get_next_line` | [Original get_next_line](https://github.com/rafav99/get_next_line) (2021) | Original mandatory/bonus versions preserved under `original/`; a separate integration implementation avoids duplicate libft symbols and supports multiple descriptors. |
| `push_swap` | Recovered local 2022 drafts | Working reconstruction of the original chunk-based sorting idea; original drafts in `prototype/`. |
| `philosophers` | Recovered local sources | Standalone pthread program, independent of shared libs. |
| `minishell` | Recovered local sources | Parser, expansion, pipelines and builtins; depends on libft, ft_printf extensions and GNU Readline. |
| `so_long` | [Original so_long](https://github.com/rafav99/so_long) (2023) | Original game, `.ber` map and `.xpm` artwork; links to shared libft/printf/gnl instead of bundled duplicates. Mac keycodes remapped on Linux. |

The four original GitHub repositories are pinned to specific commit IDs inside `tools/bootstrap.py`. Their source is imported automatically into this workspace the first time you run `make`. This ZIP contains the importer and local projects; **an internet connection is required once to retrieve the original GitHub files and game artwork.** Afterwards the project directories contain normal source files that you can commit into your monorepo without submodules.

## Publish to your 42-Madrid GitHub repository

From this extracted folder, with Git configured and authenticated, run `bash publish.sh`. It imports the original source repositories, attempts the full build and automated tests, then commits and pushes the integrated sources. If a build or test fails, it stops **before** the push; it never force-pushes over an existing `main` branch. If MiniLibX or Readline system dependencies are missing, install the packages below first. The publisher requires online access to GitHub.

## Ubuntu / Debian setup

```bash
sudo apt update
sudo apt install build-essential git python3 libreadline-dev libx11-dev libxext-dev libbsd-dev zlib1g-dev
make
make test
```

For a non-graphical machine or to build without MiniLibX, use `make core` rather than `make`. MiniLibX is downloaded into `third_party/minilibx-linux/` on first `so_long` build; this unmodified external graphics dependency is deliberately not represented as original 42 work. Linux graphics requires an X server (XWayland usually works under GNOME Wayland).

Individual projects can be built with `make -C <project>` **after** `make setup`. Use `make clean`, `make fclean` and `make re` from the root. `make setup` is idempotent after a successful import.

## Dependency graph

```text
libft ────┬──── ft_printf ───── minishell (+readline)
          │         │
          │         └──── so_long (+MiniLibX)
          ├──── get_next_line ─┘
          └──── push_swap

philosophers (independent)
```

## Verification and provenance

The locally reconstructed `push_swap` and recovered `philosophers` have automated tests; `integration/tests/test_gnl.py` tests the reusable GNL once source imports are complete. Source files under `get_next_line/original` remain recognizable as the author's original 2021 code; integration fixes are explicitly separate. The graphical program `so_long` originally targeted macOS and needs a live graphical session for end-to-end verification. This repository is an integration workspace for GitHub, **not** a claim that the resulting shared layout passes the original isolated 42 project evaluations, Norminette, or Valgrind.
