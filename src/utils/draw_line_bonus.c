#include "../../inc/cub3d.h"

void	drawlinedda_minimap(int x, int y, int color, t_container *content)
{
	t_line_params	*line;
	int				dx_abs;
	int				dy_abs;
	int				i;

	line = content->line_par;
	line->dx = line->end_x - x;
	line->dy = line->end_y - y;
	dx_abs = abs(line->dx);
	dy_abs = abs(line->dy);
	if (dx_abs > dy_abs)
	{
		line->steps = dx_abs;
	}
	else
	{
		line->steps = dy_abs;
	}
	if (line->steps == 0)
	{
		print_pxt(x, y, color, content);
		return ;
	}
	line->xInc = (float)line->dx / (float)line->steps;
	line->yInc = (float)line->dy / (float)line->steps;
	line->x = (float)x;
	line->y = (float)y;
	i = 0;
	while (i <= line->steps)
	{
		print_pxt((int)roundf(line->x), (int)roundf(line->y), color, content);
		line->x += line->xInc;
		line->y += line->yInc;
		i++;
	}
}

void	initiale_minimap(t_container *content)
{
	t_minimap	*map_inf;

	map_inf = content->minimap;
	map_inf->minimap_radius = M_MAP_S / (2 * M_CELL);
	map_inf->player_map_x = (int)(content->plr.x / PIXEL_SIZE);
	map_inf->player_map_y = (int)(content->plr.y / PIXEL_SIZE);
	map_inf->offset_x = (content->plr.x / PIXEL_SIZE) - map_inf->player_map_x;
	map_inf->offset_y = (content->plr.y / PIXEL_SIZE) - map_inf->player_map_y;
}
