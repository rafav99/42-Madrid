#include "so_long.h"
#include "../ft_printf/ft_printf.h"
#include <stdint.h>
#include <string.h>

#define TILE 64

typedef struct s_sprite
{
	void	*image;
	char	*pixels;
	int	width;
	int	height;
	int	stride;
	int	bpp;
} t_sprite;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	void		*frame;
	char		*frame_pixels;
	int		frame_stride;
	int		cols;
	int		rows;
	int		px;
	int		py;
	int		moves;
	int		face_left;
	char		*map;
	t_sprite	floor;
	t_sprite	wall;
	t_sprite	book;
	t_sprite	exit_closed;
	t_sprite	exit_open;
	t_sprite	bug;
	t_sprite	bug_left;
} t_game;

static void fail(const char *detail)
{
	ft_dprintf(2, "Error: %s\n", detail);
	exit(1);
}

static void load_sprite(t_game *g, t_sprite *s, char *path)
{
	int endian;

	s->image = mlx_xpm_file_to_image(g->mlx, path, &s->width, &s->height);
	if (!s->image)
		fail(path);
	s->pixels = mlx_get_data_addr(s->image, &s->bpp, &s->stride, &endian);
	if (!s->pixels || s->bpp != 32)
		fail("Unsupported XPM pixel format");
}

static void draw_sprite(t_game *g, t_sprite *s, int left, int top)
{
	int x;
	int y;
	int dx;
	int dy;
	uint32_t color;

	y = 0;
	while (y < s->height)
	{
		dy = top + y;
		x = 0;
		while (x < s->width)
		{
			dx = left + x;
			if (dx >= 0 && dx < g->cols * TILE && dy >= 0 && dy < g->rows * TILE)
			{
				memcpy(&color, s->pixels + y * s->stride + x * 4, 4);
				if ((color & 0xff000000U) != 0xff000000U)
					memcpy(g->frame_pixels + dy * g->frame_stride + dx * 4, &color, 4);
			}
			x++;
		}
		y++;
	}
}

static int map_offset(t_game *g, int x, int y)
{
	return (y * (g->cols + 1) + x);
}

static void draw_floor(t_game *g, int col, int row)
{
	int x;
	int y;

	y = 0;
	while (y < TILE)
	{
		x = 0;
		while (x < TILE)
		{
			draw_sprite(g, &g->floor, col * TILE + x, row * TILE + y);
			x += 16;
		}
		y += 16;
	}
}

static void draw_scene(t_game *g)
{
	int row;
	int col;
	char tile;
	int no_books;

	row = 0;
	no_books = (countbooks(g->map) == 0);
	while (row < g->rows)
	{
		col = 0;
		while (col < g->cols)
		{
			tile = g->map[map_offset(g, col, row)];
			if (tile == '1')
				draw_sprite(g, &g->wall, col * TILE, row * TILE);
			else
				draw_floor(g, col, row);
			col++;
		}
		row++;
	}
	row = 0;
	while (row < g->rows)
	{
		col = 0;
		while (col < g->cols)
		{
			tile = g->map[map_offset(g, col, row)];
			if (tile == 'C')
				draw_sprite(g, &g->book, col * TILE + 6, row * TILE + 8);
			if (tile == 'E')
			{
				if (no_books)
					draw_sprite(g, &g->exit_open, col * TILE - 15, row * TILE - 10);
				else
					draw_sprite(g, &g->exit_closed, col * TILE - 25, row * TILE + 2);
			}
			col++;
		}
		row++;
	}
	if (g->face_left)
		draw_sprite(g, &g->bug_left, g->px * TILE + 10, g->py * TILE + 10);
	else
		draw_sprite(g, &g->bug, g->px * TILE + 10, g->py * TILE + 10);
	mlx_put_image_to_window(g->mlx, g->window, g->frame, 0, 0);
}

static int close_game(t_game *g)
{
	mlx_destroy_image(g->mlx, g->frame);
	mlx_destroy_image(g->mlx, g->floor.image);
	mlx_destroy_image(g->mlx, g->wall.image);
	mlx_destroy_image(g->mlx, g->book.image);
	mlx_destroy_image(g->mlx, g->exit_closed.image);
	mlx_destroy_image(g->mlx, g->exit_open.image);
	mlx_destroy_image(g->mlx, g->bug.image);
	mlx_destroy_image(g->mlx, g->bug_left.image);
	mlx_destroy_window(g->mlx, g->window);
	mlx_destroy_display(g->mlx);
	free(g->mlx);
	exit(0);
}

static int close_hook(void *param)
{
	return (close_game((t_game *)param));
}

static int key_hook(int key, void *param)
{
	t_game *g;
	int dx;
	int dy;
	char next;

	g = (t_game *)param;
	dx = 0;
	dy = 0;
	if (key == 65307)
		return (close_game(g));
	if (key == 97 || key == 65361)
		dx = -1;
	else if (key == 100 || key == 65363)
		dx = 1;
	else if (key == 119 || key == 65362)
		dy = -1;
	else if (key == 115 || key == 65364)
		dy = 1;
	else
		return (0);
	if (g->px + dx < 0 || g->px + dx >= g->cols ||
		g->py + dy < 0 || g->py + dy >= g->rows)
		return (0);
	next = g->map[map_offset(g, g->px + dx, g->py + dy)];
	if (next == '1' || (next == 'E' && countbooks(g->map) != 0))
		return (0);
	g->px += dx;
	g->py += dy;
	if (dx != 0)
		g->face_left = (dx < 0);
	if (next == 'C')
		g->map[map_offset(g, g->px, g->py)] = '0';
	g->moves++;
	ft_printf("Moves: %d\n", g->moves);
	if (next == 'E')
	{
		ft_printf("You win!\n");
		return (close_game(g));
	}
	draw_scene(g);
	return (0);
}

static void load_images(t_game *g)
{
	load_sprite(g, &g->floor, "imgs/wooden.xpm");
	load_sprite(g, &g->wall, "imgs/finshelf.xpm");
	load_sprite(g, &g->book, "imgs/book.xpm");
	load_sprite(g, &g->exit_closed, "imgs/blackexit.xpm");
	load_sprite(g, &g->exit_open, "imgs/exactive.xpm");
	load_sprite(g, &g->bug, "imgs/bug.xpm");
	load_sprite(g, &g->bug_left, "imgs/bugrev.xpm");
}

void render(char *map, int nrows, int len)
{
	t_game g;
	int i;
	int endian;
	int bpp;

	(void)nrows;
	(void)len;
	memset(&g, 0, sizeof(g));
	g.map = map;
	while (map[g.cols] && map[g.cols] != '\n')
		g.cols++;
	i = 0;
	while (map[i])
	{
		if (map[i] == '\n')
			g.rows++;
		i++;
	}
	if (i > 0 && map[i - 1] != '\n')
		g.rows++;
	if (!g.cols || !g.rows)
		fail("Empty map");
	i = 0;
	while (i < g.cols * g.rows)
	{
		if (map[map_offset(&g, i % g.cols, i / g.cols)] == 'P')
		{
			g.px = i % g.cols;
			g.py = i / g.cols;
		}
		i++;
	}
	g.mlx = mlx_init();
	if (!g.mlx)
		fail("Cannot connect to X11 (is XWayland running?)");
	g.window = mlx_new_window(g.mlx, g.cols * TILE, g.rows * TILE, "The library");
	if (!g.window)
		fail("Cannot create the game window");
	g.frame = mlx_new_image(g.mlx, g.cols * TILE, g.rows * TILE);
	if (!g.frame)
		fail("Cannot create the frame buffer");
	g.frame_pixels = mlx_get_data_addr(g.frame, &bpp, &g.frame_stride, &endian);
	if (!g.frame_pixels || bpp != 32)
		fail("Unsupported frame pixel format");
	load_images(&g);
	draw_scene(&g);
	mlx_key_hook(g.window, key_hook, &g);
	mlx_hook(g.window, 17, 0, close_hook, &g);
	mlx_loop(g.mlx);
}
