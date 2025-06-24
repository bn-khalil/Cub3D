#include "../../inc/cub3d.h"

void	draw_clean(int x, int y, int color, t_container *content)
{
	int	i;
	int	j;

	i = 0;
	while (i < PIXEL_SIZE)
	{
		j = 0;
		while (j < PIXEL_SIZE)
		{
			print_pxt(x + i, y + j, color, content);
			j++;
		}
		i++;
	}
}

void	clear_map_after_player(t_container *content)
{
	int	x;
	int	y;

	y = 0;
	while (y < content->map_h)
	{
		x = 0;
		while (x < content->map_w)
		{
			draw_clean(x * PIXEL_SIZE, y * PIXEL_SIZE, 0x000000, content);
			x++;
		}
		y++;
	}
}
