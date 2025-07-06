/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizantal_calcule.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:01:18 by kben-tou          #+#    #+#             */
/*   Updated: 2025/07/03 15:01:19 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	init_h_intercepts(t_container *content, int i,
		t_horizontal_param *horiz)
{
	horiz->y_h_intercept = floor(content->plr.y / PIXEL_SIZE) * PIXEL_SIZE;
	if (content->rays[i].is_ray_down)
	{
		horiz->y_h_intercept += PIXEL_SIZE;
	}
	horiz->x_h_intercept = content->plr.x + (horiz->y_h_intercept
			- content->plr.y) / tan(content->rays[i].ray_angle);
}

static void	calc_h_steps(t_container *content, int i, t_horizontal_param *horiz)
{
	horiz->y_h_step = PIXEL_SIZE;
	if (content->rays[i].is_ray_up)
	{
		horiz->y_h_step *= -1;
	}
	horiz->x_h_step = PIXEL_SIZE / tan(content->rays[i].ray_angle);
	if ((content->rays[i].is_ray_left && horiz->x_h_step > 0)
		|| (content->rays[i].is_ray_right && horiz->x_h_step < 0))
	{
		horiz->x_h_step *= -1;
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
		t_horizontal_param *horiz)
{
	float	curr_x;
	float	curr_y;
	float	map_max_w;
	float	map_max_h;

	curr_x = horiz->x_h_intercept;
	curr_y = horiz->y_h_intercept;
	map_max_w = content->map_w * PIXEL_SIZE;
	map_max_h = content->map_h * PIXEL_SIZE;
	while (curr_x >= 0 && curr_x <= map_max_w && curr_y >= 0
		&& curr_y <= map_max_h)
	{
		if (check_h_wall_hit(content, i, curr_x, curr_y))
		{
			break ;
		}
		curr_x += horiz->x_h_step;
		curr_y += horiz->y_h_step;
	}
}

void	get_the_horizantal(t_container *content, int i)
{
	t_horizontal_param	horiz;

	ft_memset(&horiz, 0, sizeof(t_horizontal_param));
	init_h_intercepts(content, i, &horiz);
	calc_h_steps(content, i, &horiz);
	find_horizontal_hit_point(content, i, &horiz);
	return ;
}
