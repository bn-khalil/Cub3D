#include "../../inc/cub3d.h"

void	draw_border(t_container *content)
{
	int	i;

	i = 0;
	while (i < M_MAP_S)
	{
		print_pxt(M_M_X + i, M_M_Y, 0xFFFFFF, content);
		print_pxt(M_M_X + i, M_M_Y + M_MAP_S - 1, 0xFFFFFF, content);
		print_pxt(M_M_X, M_M_Y + i, 0xFFFFFF, content);
		print_pxt(M_M_X + M_MAP_S - 1, M_M_Y + i, 0xFFFFFF, content);
		i++;
	}
}

void	clear_mini_map(t_container *content)
{
	int	y;
	int	x;

	y = 0;
	while (y < M_MAP_S)
	{
		x = 0;
		while (x < M_MAP_S)
		{
			print_pxt(M_M_X + x, M_M_Y + y, 0x000000, content);
			x++;
		}
		y++;
	}
}

void	draw_minimap_cell(t_container *content, int color)
{
	int	py;
	int	px;
	int	draw_x;
	int	draw_y;

	py = 0;
	while (py < M_CELL)
	{
		px = 0;
		while (px < M_CELL)
		{
			draw_x = content->minimap->minimap_cell_x + px;
			draw_y = content->minimap->minimap_cell_y + py;
			if (draw_x >= M_M_X && draw_x < M_M_X + M_MAP_S && draw_y >= M_M_Y
				&& draw_y < M_M_Y + M_MAP_S)
				print_pxt(draw_x, draw_y, color, content);
			px++;
		}
		py++;
	}
}

int	get_color(t_container *content, int dx, int dy)
{
	int	color;
	int	map_x;
	int	map_y;

	color = 0x000000;
	map_x = content->minimap->player_map_x + dx;
	map_y = content->minimap->player_map_y + dy;
	if (map_x >= 0 && map_x < content->map_w && map_y >= 0
		&& map_y < content->map_h)
	{
		if (content->map[map_y][map_x] && content->map[map_y][map_x] == '1')
		{
			color = 0xFFFFFF;
		}
		else
			color = 0x404040;
	}
	return (color);
}

void	render_minimap(t_container *content)
{
	t_minimap	*map_inf;
	int			dy;
	int			dx;

	map_inf = content->minimap;
	initiale_minimap(content);
	clear_mini_map(content);
	dy = -map_inf->minimap_radius;
	while (dy <= map_inf->minimap_radius)
	{
		dx = -map_inf->minimap_radius;
		while (dx <= map_inf->minimap_radius)
		{
			map_inf->minimap_cell_x = M_M_X + ((float)M_MAP_S / 2) + ((dx
						- map_inf->offset_x) * M_CELL);
			map_inf->minimap_cell_y = M_M_Y + ((float)M_MAP_S / 2) + ((dy
						- map_inf->offset_y) * M_CELL);
			draw_minimap_cell(content, get_color(content, dx, dy));
			dx++;
		}
		dy++;
	}
	put_player_map(content);
	draw_border(content);
}
