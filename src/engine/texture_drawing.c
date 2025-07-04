/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_drawing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:57:13 by kben-tou          #+#    #+#             */
/*   Updated: 2025/07/02 17:13:06 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	texture_init(t_container *content)
{
	t_config	*iter;
	int			i;

	if (!content || !content->src.mlx)
		ft_error("Error: MLX not initialized", content);
	iter = content->confs;
	i = 0;
	while (iter)
	{
		if (!iter->value)
			ft_error("Error: texture path is NULL", content);
		iter->img = mlx_xpm_file_to_image(content->src.mlx, iter->value, \
			&iter->txr_w, &iter->txr_h);
		if (!iter->img)
			ft_error("Error: failed to load texture image", content);
		iter->buffer_pos = mlx_get_data_addr(iter->img, \
			&iter->pixel_bits_number, &iter->len_with_pixels, &iter->endian);
		if (!iter->buffer_pos)
			ft_error("Error: failed to get texture buffer", content);
		i++;
		iter = iter->next;
	}
}

void	draw_ceilling_floor(t_container *content, t_ray ray, int i)
{
	ray.c = -1;
	while (++ray.c < ray.wall_top_pixel)
		print_pxt(i * WALL_COL_WIDH, ray.c, content->ceiling_color, content);
	ray.f = ray.botm_pixel - 1;
	while (++ray.f < MAP_H)
		print_pxt(i * WALL_COL_WIDH, ray.f, content->floor_color, content);
}

void	draw_texture_on_screen(t_container *content, t_ray ray, \
	t_config *texture, int i)
{
	int		tex_x;
	int		tex_y;
	float	rel_y;
	int		y;

	y = ray.wall_top_pixel - 1;
	if (ray.was_vertical)
		tex_x = (int)fmod((ray.wall_hit_y * texture->txr_w / PIXEL_SIZE), \
			texture->txr_w);
	else
		tex_x = (int)fmod((ray.wall_hit_x * texture->txr_w / PIXEL_SIZE), \
			texture->txr_w);
	while (++y < ray.botm_pixel)
	{
		rel_y = (float)(y - (MAP_H / 2)) / ray.wall_hight;
		tex_y = (int)((0.5f + rel_y) * texture->txr_h);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= texture->txr_h)
			tex_y = texture->txr_h - 1;
		ray.color = ((unsigned int *)texture->buffer_pos) \
		[tex_y * texture->txr_w + tex_x];
		print_pxt(i * WALL_COL_WIDH, y, ray.color, content);
	}
}
