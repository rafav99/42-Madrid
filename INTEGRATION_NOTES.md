# Integration notes

## Original sources and modifications

The local `minishell`, `philosophers`, and `push_swap/prototype` source files come from the user's supplied ZIP archives. The main `push_swap/src` was reconstructed from the chunk-based strategy in those drafts and is not claimed to be a historical submitted version.

`tools/bootstrap.py` imports the following original GitHub repositories at pinned commits:

| Source repository | Commit |
| --- | --- |
| `rafav99/Libft` | `0695a86c1509cd885e969aa36910cde4df3b7cd5` |
| `rafav99/ft_printf` | `92125638ac8c3f6bd308d3cc8109f5cd9e920ac5` |
| `rafav99/get_next_line` | `d1d6d177185e343066c0b0cd00205f0630d9f4a9` |
| `rafav99/so_long` | `7d98688b578c0efcfb2e74edef23158e5424b23d` |

The importer copies original files (not a git submodule), then makes integration-specific changes:

- **libft**: compiles all functions including list helpers and adds `ft_strcmp`, `ft_isspace` extensions.
- **ft_printf**: removes the duplicate implementation of `ft_strlen` in `printf_put.c`; adds `ft_vsprintf` and `ft_dprintf` extracted from the user-provided minishell project.
- **get_next_line**: preserves all six original files under `original/`. Its reusable build is isolated to a shared file-descriptor-aware implementation that links against libft instead of re-declaring the same string functions.
- **so_long**: keeps original maps and sprites, archives its vendored printf/gnl under `original_dependencies`, uses shared libraries, replaces an unsafe map-reading function and a missing string terminator allocation, and adapts Linux keyboard codes. Its original macOS Makefile is archived.
- **minishell**: retains shell-specific parsing functions while using the shared libraries for standard helpers and error formatting.

## Verification status

- `philosophers`: local stress and invalid-input tests passed.
- `push_swap`: local 100 and 500 item sorting tests passed **against the previous shared libft-compatible helpers**, not against a freshly imported original Libft.
- `get_next_line` integration: multi-FD smoke test passed with previous shared libft-compatible helpers.
- External GitHub downloads cannot be performed in this preparation environment, so no claim of a complete integrated compilation is made. The `make` importer and the `so_long` MiniLibX integration require a network-enabled machine for the first build.
- `minishell` requires the GNU Readline development package; the prepared environment lacks its headers.
- No independent GUI runtime test of `so_long` has been performed.
