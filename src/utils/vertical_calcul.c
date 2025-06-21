#include "../../inc/cub3d.h"

static void	init_v_intercepts(t_container *content, int i, float *x_v_intercept,
		float *y_v_intercept)
{
	*x_v_intercept = floor(content->plr.x / PIXEL_SIZE) * PIXEL_SIZE;
	if (content->rays[i].is_ray_right)
	{
		*x_v_intercept += PIXEL_SIZE;
	}
	*y_v_intercept = content->plr.y + (*x_v_intercept - content->plr.x)
		* tan(content->rays[i].ray_angle);
}

static void	calc_v_steps(t_container *content, int i, float *x_v_step,
		float *y_v_step)
{
	*x_v_step = PIXEL_SIZE;
	if (content->rays[i].is_ray_left)
	{
		*x_v_step *= -1;
	}
	*y_v_step = PIXEL_SIZE * tan(content->rays[i].ray_angle);
	if ((content->rays[i].is_ray_up && *y_v_step > 0)
		|| (content->rays[i].is_ray_down && *y_v_step < 0))
	{
		*y_v_step *= -1;
	}
}

// Helper function: Finds vertical hit point and updates ray info
// (Less than 25 lines, 5 variables)
static void	find_vertical_hit_point(t_container *content, int i, float next_v_x,
		float next_v_y, float x_v_step, float y_v_step)
{
	float	curr_x;
	float	curr_y;
	float	check_x_adjusted;
	float	map_max_w;
	float	map_max_h;

	curr_x = next_v_x;
	curr_y = next_v_y;
	map_max_w = content->map_w * PIXEL_SIZE;
	map_max_h = content->map_h * PIXEL_SIZE;
	while (curr_x >= 0 && curr_x <= map_max_w && curr_y >= 0
		&& curr_y <= map_max_h)
	{
		check_x_adjusted = curr_x;
		if (content->rays[i].is_ray_left)
			check_x_adjusted -= 1.0;
		if (is_wall(check_x_adjusted, curr_y, content))
		{
			content->rays[i].is_hit_vertical = 1;
			content->rays[i].ver_hit_x = curr_x;
			content->rays[i].ver_hit_y = curr_y;
			break ;
		}
		curr_x += x_v_step;
		curr_y += y_v_step;
	}
}

void	get_vertical(t_container *content, int i)
{
	float	x_v_intercept;
	float	y_v_intercept;
	float	x_v_step;
	float	y_v_step;

	// Empty line after declarations
	init_v_intercepts(content, i, &x_v_intercept, &y_v_intercept);
	calc_v_steps(content, i, &x_v_step, &y_v_step);
	find_vertical_hit_point(content, i, x_v_intercept, y_v_intercept, x_v_step,
		y_v_step);
	return ; // Return with parentheses is preferred by norminette
}
