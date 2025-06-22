#include "../../inc/cub3d.h"

void	draw_horizontal_cross(int center_x, int center_y, int color,
		t_container *content)
{
	int	dx;
	int	t;
	int	half;
	int	thickness;

	half = 2;
	thickness = 1;
	dx = -half;
	while (dx <= half)
	{
		t = -thickness;
		while (t <= thickness)
		{
			print_pxt(center_x + dx, center_y + t, color, content);
			t++;
		}
		dx++;
	}
}

void	draw_vertical_cross(int center_x, int center_y, int color,
		t_container *content)
{
	int	dy;
	int	t;
	int	half;
	int	thickness;

	half = 2;
	thickness = 1;
	dy = -half;
	while (dy <= half)
	{
		t = -thickness;
		while (t <= thickness)
		{
			print_pxt(center_x + t, center_y + dy, color, content);
			t++;
		}
		dy++;
	}
}

void	draw_diagonal_corners(int center_x, int center_y, int color,
		t_container *content)
{
	int	i;
	int	sign;
	int	half;

	half = 2;
	i = 0;
	while (i < 2)
	{
		sign = -1;
		if (i != 0)
			sign = 1;
		print_pxt(center_x + sign * half, center_y + sign * half, color,
			content);
		print_pxt(center_x + sign * half, center_y - sign * half, color,
			content);
		i++;
	}
}

void	draw_player_shape_minimap(int center_x, int center_y, int color,
		t_container *content)
{
	draw_horizontal_cross(center_x, center_y, color, content);
	draw_vertical_cross(center_x, center_y, color, content);
	draw_diagonal_corners(center_x, center_y, color, content);
}

void	put_player_map(t_container *content)
{
	int		player_minimap_x;
	int		player_minimap_y;
	float	dir_length;

	player_minimap_x = M_M_X + (M_MAP_S / 2);
	player_minimap_y = M_M_Y + (M_MAP_S / 2);
	draw_player_shape_minimap(player_minimap_x, player_minimap_y, 0x00FF00,
		content);
	dir_length = 11.0;
	content->line_par->end_x = player_minimap_x
		+ (int)(cos(content->plr.r_angle) * dir_length);
	content->line_par->end_y = player_minimap_y
		+ (int)(sin(content->plr.r_angle) * dir_length);
	drawlinedda_minimap(player_minimap_x, player_minimap_y, 0xFF0000, content);
}
