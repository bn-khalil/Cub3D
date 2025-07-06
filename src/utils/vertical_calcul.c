/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_calcul.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:01:22 by kben-tou          #+#    #+#             */
/*   Updated: 2025/07/03 15:01:23 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	init_v_intercepts(t_container *content, int i,
		t_vertical_params *vertical)
{
	vertical->x_v_intercept = floor(content->plr.x / PIXEL_SIZE) * PIXEL_SIZE;
	if (content->rays[i].is_ray_right)
	{
		vertical->x_v_intercept += PIXEL_SIZE;
	}
	vertical->y_v_intercept = content->plr.y + (vertical->x_v_intercept
			- content->plr.x) * tan(content->rays[i].ray_angle);
}

static void	calc_v_steps(t_container *content, int i,
		t_vertical_params *vertical)
{
	vertical->x_v_step = PIXEL_SIZE;
	if (content->rays[i].is_ray_left)
	{
		vertical->x_v_step *= -1;
	}
	vertical->y_v_step = PIXEL_SIZE * tan(content->rays[i].ray_angle);
	if ((content->rays[i].is_ray_up && vertical->y_v_step > 0)
		|| (content->rays[i].is_ray_down && vertical->y_v_step < 0))
	{
		vertical->y_v_step *= -1;
	}
}

static int	check_v_wall_hit(t_container *content, int i, float curr_x,
		float curr_y)
{
	float	check_x_adjusted;

	check_x_adjusted = curr_x;
	if (content->rays[i].is_ray_left)
		check_x_adjusted -= 1.0;
	if (is_wall(check_x_adjusted, curr_y, content))
	{
		content->rays[i].is_hit_vertical = 1;
		content->rays[i].ver_hit_x = curr_x;
		content->rays[i].ver_hit_y = curr_y;
		return (1);
	}
	return (0);
}

static void	find_vertical_hit_point(t_container *content, int i,
		t_vertical_params *vertical)
{
	float	curr_x;
	float	curr_y;
	float	map_max_w;
	float	map_max_h;

	curr_x = vertical->x_v_intercept;
	curr_y = vertical->y_v_intercept;
	map_max_w = content->map_w * PIXEL_SIZE;
	map_max_h = content->map_h * PIXEL_SIZE;
	while (curr_x >= 0 && curr_x <= map_max_w && curr_y >= 0
		&& curr_y <= map_max_h)
	{
		if (check_v_wall_hit(content, i, curr_x, curr_y))
			break ;
		curr_x += vertical->x_v_step;
		curr_y += vertical->y_v_step;
	}
}

void	get_vertical(t_container *content, int i)
{
	t_vertical_params	vertical;

	ft_memset(&vertical, 0, sizeof(t_vertical_params));
	init_v_intercepts(content, i, &vertical);
	calc_v_steps(content, i, &vertical);
	find_vertical_hit_point(content, i, &vertical);
	return ;
}
