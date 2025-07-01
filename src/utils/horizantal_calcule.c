#include "../../inc/cub3d.h"

static void	init_h_intercepts(t_container *content, int i, float *y_intercept,
		float *x_intercept)
{
	*y_intercept = floor(content->plr.y / PIXEL_SIZE) * PIXEL_SIZE;
	if (content->rays[i].is_ray_down)
	{
		*y_intercept += PIXEL_SIZE;
	}
	*x_intercept = content->plr.x + (*y_intercept - content->plr.y)
		/ tan(content->rays[i].ray_angle);
}


static void	calc_h_steps(t_container *content, int i, float *y_step,
		float *x_step)
{
	*y_step = PIXEL_SIZE;
	if (content->rays[i].is_ray_up)
	{
		*y_step *= -1;
	}
	*x_step = PIXEL_SIZE / tan(content->rays[i].ray_angle);
	if ((content->rays[i].is_ray_left && *x_step > 0)
		|| (content->rays[i].is_ray_right && *x_step < 0))
	{
		*x_step *= -1;
	}
}

static int	check_h_wall_hit(t_container *content, int i, float next_h_x,
		float next_h_y)
{
	if (content->rays[i].is_ray_up)
	{
		if (is_wall(next_h_x, next_h_y - 1, content))
		{
			content->rays[i].is_hit_horizontal = 1;
			content->rays[i].horiz_hit_x = next_h_x;
			content->rays[i].horiz_hit_y = next_h_y;
			return (1);
		}
	}
	else if (is_wall(next_h_x, next_h_y, content))
	{
		content->rays[i].is_hit_horizontal = 1;
		content->rays[i].horiz_hit_x = next_h_x;
		content->rays[i].horiz_hit_y = next_h_y;
		return (1);
	}
	return (0);
}


static void	find_horizontal_hit_point(t_container *content, int i,
		float next_h_x, float next_h_y, float x_step, float y_step)
{
	float	curr_x;
	float	curr_y;
	float	map_max_w;
	float	map_max_h;

	curr_x = next_h_x;
	curr_y = next_h_y;
	map_max_w = content->map_w * PIXEL_SIZE;
	map_max_h = content->map_h * PIXEL_SIZE;
	while (curr_x >= 0 && curr_x <= map_max_w && curr_y >= 0
		&& curr_y <= map_max_h)
	{
		if (check_h_wall_hit(content, i, curr_x, curr_y))
		{
			break ;
		}
		curr_x += x_step;
		curr_y += y_step;
	}
}

void	get_the_horizantal(t_container *content, int i)
{
	float	y_intercept;
	float	x_intercept;
	float	y_step;
	float	x_step;

	init_h_intercepts(content, i, &y_intercept, &x_intercept);
	calc_h_steps(content, i, &y_step, &x_step);
	find_horizontal_hit_point(content, i, x_intercept, y_intercept, x_step,
		y_step);
	return ;
}
