# get_next_line

Read from a file descriptor **one line at a time**, with a configurable buffer size.

The implementation preserves unread data between calls and maintains separate state for different file descriptors. The `original/` directory contains my initial regular and bonus versions; the integrated version reuses [libft](../libft/).

```bash
make -C libft
make -C get_next_line BUFFER_SIZE=42
```

**Focus:** buffered I/O, allocation, static state and file descriptors.
