# Publishing 42-Madrid

The destination repository is `https://github.com/rafav99/42-Madrid` (empty when this bundle was prepared).

On your Ubuntu installation, install dependencies listed in `README.md`, extract the ZIP, then run:

```sh
bash publish.sh
```

The publisher is intentionally conservative: it downloads the four original repositories at pinned commit SHAs, integrates the libraries, builds each project, runs the available non-GUI tests, and publishes **only if those checks pass**. It cannot verify the visual behavior of `so_long`, which requires a running X server / XWayland.

Original source is not replaced or deleted in your existing individual GitHub repositories. The `42-Madrid` monorepo receives independent copies of the files. No `git push --force` is used; it refuses to overwrite a populated main branch.

If you prefer to prepare locally without publishing, run `make setup && make core && make test` separately.

## Fix for the first importer error (October 2026)

If an older copy fails when importing `libft` with `FileNotFoundError` on
`libft/ft_memset.c`, the previous importer did not create its destination
folders. In the older extracted repository, run:

```bash
mkdir -p libft ft_printf get_next_line so_long
bash publish.sh
```

This corrected archive already fixes that problem in `tools/bootstrap.py`.

The full build also requires GitHub network access, Readline headers, and
MiniLibX/X11 development dependencies; a later error should be diagnosed
separately rather than assumed to be the same directory bug.
