/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:54:53 by kben-tou          #+#    #+#             */
/*   Updated: 2025/07/03 14:54:54 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

float	get_vector_dis(t_container *content, float nex_x, float nex_y)
{
	return (sqrt((nex_x - content->plr.x) * (nex_x - content->plr.x) + (nex_y
				- content->plr.y) * (nex_y - content->plr.y)));
}

void	get_the_smallest(t_ray *ray, float ray_angle, float player_angle)
{
	if (ray->horiz_distance < ray->ver_distance)
	{
		ray->wall_hit_x = ray->horiz_hit_x;
		ray->wall_hit_y = ray->horiz_hit_y;
		ray->distance = ray->horiz_distance;
		ray->was_vertical = 0;
	}
	else
	{
		ray->wall_hit_x = ray->ver_hit_x;
		ray->wall_hit_y = ray->ver_hit_y;
		ray->distance = ray->ver_distance;
		ray->was_vertical = 1;
	}
	ray->distance *= cos(ray_angle - player_angle);
}

void	get_the_ray_length(t_container *content, int i)
{
	if (content->rays[i].is_hit_horizontal)
	{
		content->rays[i].horiz_distance = get_vector_dis(content,
				content->rays[i].horiz_hit_x, content->rays[i].horiz_hit_y);
	}
	else
		content->rays[i].horiz_distance = FLT_MAX;
	if (content->rays[i].is_hit_vertical)
	{
		content->rays[i].ver_distance = get_vector_dis(content,
				content->rays[i].ver_hit_x, content->rays[i].ver_hit_y);
	}
	else
		content->rays[i].ver_distance = FLT_MAX;
	get_the_smallest(&content->rays[i], content->rays[i].ray_angle,
		content->plr.r_angle);
}

void	ray_info(t_container *content)
{
	int		i;
	float	ray_angle;

	i = -1;
	ray_angle = fix_angle(content->plr.r_angle - (FOV / 2));
	while (++i < content->num_rays)
	{
		content->rays[i].is_hit_horizontal = 0;
		content->rays[i].is_hit_vertical = 0;
		content->rays[i].ray_angle = ray_angle;
		content->rays[i].is_ray_down = ray_angle > 0 && ray_angle < PI;
		content->rays[i].is_ray_up = !content->rays[i].is_ray_down;
		content->rays[i].is_ray_right = ray_angle < (PI / 2) || ray_angle > 1.5
			* PI;
		content->rays[i].is_ray_left = !content->rays[i].is_ray_right;
		get_the_horizantal(content, i);
		get_vertical(content, i);
		get_the_ray_length(content, i);
		ray_angle = fix_angle(ray_angle + (FOV / content->num_rays));
	}
}
