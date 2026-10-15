# push_swap

Sort integer inputs using two stacks and a restricted instruction set.

The program validates signed integers, rejects duplicates, normalizes values into ranks and prints stack operations (`sa`, `pb`, `ra`, `rrb`, etc.) rather than the sorted array. It uses dedicated strategies for small inputs and a chunk-based approach for larger ones.

```bash
make -C libft
make -C push_swap
./push_swap/push_swap 3 2 1
python3 push_swap/tests.py
```

The randomized test suite checks correctness and instruction counts. One run averaged about 667 operations for 100 values and 5,866 for 500 values; these are measured averages, not guarantees. `prototype/` preserves earlier sorting experiments from which this implementation was rebuilt.

**Focus:** algorithms, stacks, rank normalization and performance.
