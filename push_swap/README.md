# push_swap

Working reconstruction based on the original 2022 experimental chunk-sorting implementation, preserved in `prototype/`.

For inputs of up to five integers, the solver applies a dedicated small-stack strategy. For larger inputs, it ranks the values, transfers consecutive rank chunks from A to B, rotates B to keep smaller ranks deeper, then retrieves the maximum from B to A. Only legal push_swap operations are printed.

```sh
make -C push_swap
./push_swap/push_swap 3 2 1
./push_swap/push_swap "3 2 1"
```

Rejects duplicate, malformed and out-of-range signed 32-bit integers with `Error` on stderr; an empty invocation produces no output. Links the shared `../libft/libft.a`, rather than duplicating `ft_*` routines. Original drafts are kept intact as historical source materials in `prototype/`.

This is a modern reconstruction, not a claim to have recovered the exact previously submitted project.

Regression tests: `python3 push_swap/tests.py` after building.

Performance note: the solution is correct on the included randomized tests; the 500-element sorting count can still be optimized. It has not been audited for the 42 Norm or evaluated by moulinette.
