/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:57:28 by kben-tou          #+#    #+#             */
/*   Updated: 2025/07/05 14:48:44 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_config	*get_texture_by_id(t_config *confs, const char *id)
{
	while (confs)
	{
		if (ft_strncmp(confs->id, id, 2) == 0)
			return (confs);
		confs = confs->next;
	}
	return (NULL);
}

void	set_ray_wall_dir(t_ray *ray, t_container *content)
{
	if (ray->was_vertical)
	{
		if (ray->ray_angle > PI / 2 && ray->ray_angle < 3 * PI / 2)
			ray->wall_dir = "WE";
		else
			ray->wall_dir = "EA";
	}
	else
	{
		if (ray->ray_angle > 0 && ray->ray_angle < PI)
			ray->wall_dir = "NO";
		else
			ray->wall_dir = "SO";
	}
}

void	strip_start_end_points(t_ray *ray, float dis_project)
{
	if (ray->distance < 0.1f)
		ray->distance = 0.1f;
	ray->wall_hight = (PIXEL_SIZE / ray->distance) * dis_project;
	ray->wall_strip_high = (int)ray->wall_hight;
	ray->wall_top_pixel = (MAP_H / 2) - (ray->wall_strip_high / 2);
	if (ray->wall_top_pixel < 0)
		ray->wall_top_pixel = 0;
	ray->botm_pixel = (MAP_H / 2) + (ray->wall_strip_high / 2);
	if (ray->botm_pixel > MAP_H)
		ray->botm_pixel = MAP_H;
}

void	convert_2d_to_3d(t_container *content)
{
	int			i;
	t_ray		ray;
	float		dis_project;
	t_config	*texture;

	i = -1;
	dis_project = (MAP_W / 2.0f) / tan(FOV / 2.0f);
	while (++i < content->num_rays)
	{
		ray = content->rays[i];
		strip_start_end_points(&ray, dis_project);
		draw_ceilling_floor(content, ray, i);
		set_ray_wall_dir(&ray, content);
		texture = get_texture_by_id(content->confs, ray.wall_dir);
		draw_texture_on_screen(content, ray, texture, i);
	}
}

int	draw_game(t_container *content)
{
	let_player_move(content);
	ray_info(content);
	convert_2d_to_3d(content);
	draw_sprite_hands(content);
	mlx_put_image_to_window(content->src.mlx, content->src.win,
		content->src.img, 0, 0);
	return (0);
}
