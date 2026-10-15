# so_long

The original game files, maps, and sprites will be imported from `rafav99/so_long` by `make setup`. The Linux integration uses MiniLibX from 42Paris.

Linux rendering uses `linux_render.c`, which composites XPM sprites over background tiles into one off-screen image and displays it once per movement. This avoids black transparency rectangles and flicker in the original macOS-oriented renderer. Original renderer files remain in the directory for reference.
