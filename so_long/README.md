# so_long — The Library

A small 2D exploration game written in C with **MiniLibX**.

Explore a library, collect all books and reach the exit. Levels are defined by `.ber` maps with walls (`1`), floor (`0`), collectibles (`C`), a player (`P`) and an exit (`E`).

- Tile-based rendering with XPM sprites
- Map shape and path validation
- Movement using WASD or the arrow keys on Linux; Escape to quit
- Framebuffer-based composition on Linux to preserve transparent sprites and eliminate flicker

## Play on Linux

From the repository root, after installing the dependencies described in the main README:

```bash
make
cd so_long
./so_long maps/mymap.ber
```

**Focus:** graph reachability, game state, events, sprite rendering and platform portability.
