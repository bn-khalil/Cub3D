/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intial_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:54:52 by kben-tou          #+#    #+#             */
/*   Updated: 2025/07/02 17:25:19 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_player(t_container *content)
{
	content->plr.up = 0;
	content->plr.down = 0;
	content->plr.left = 0;
	content->plr.right = 0;
	content->plr.speed = 3.5;
	content->plr.rotate_left = 0;
	content->plr.rotate_right = 0;
	content->num_rays = MAP_W / WALL_COL_WIDH;
	content->rays = malloc(sizeof(t_ray) * content->num_rays);
	ft_memset(content->rays, 0, sizeof(t_ray) * content->num_rays);
	if (content->plr.std_direction == 'E')
		content->plr.r_angle = 0;
	if (content->plr.std_direction == 'W')
		content->plr.r_angle = PI;
	if (content->plr.std_direction == 'S')
		content->plr.r_angle = PI / 2;
	if (content->plr.std_direction == 'N')
		content->plr.r_angle = 3 * PI / 2;
	content->plr.r_speed = 2 * (PI / 180);
	content->old_mouse_x = MAP_W / 2;
	content->mouse_press = 0;
}

void	mlx_res_init(t_container *content)
{
	init_player(content);
	content->src.mlx = mlx_init();
	content->src.win = mlx_new_window(content->src.mlx, MAP_W, MAP_H, "Cub3D");
	content->src.img = mlx_new_image(content->src.mlx, MAP_W, MAP_H);
	content->src.buffer_pos = mlx_get_data_addr(content->src.img, \
		&content->src.pixel_bits_number, \
		&content->src.len_with_pixels, &content->src.endian);
	texture_init(content);
}

void	start_the_play(t_container *content)
{
	mlx_res_init(content);
	mlx_put_image_to_window(content->src.mlx, \
		content->src.win, content->src.img, 0, 0);
	mlx_hook(content->src.win, 17, 0, ft_close, content);
	mlx_hook(content->src.win, 2, 1L << 0, key_action, content);
	mlx_hook(content->src.win, 3, 1L << 1, key_back, content);
	mlx_hook(content->src.win, 4, 1L << 2, mouse_press, content);
	mlx_hook(content->src.win, 5, 1L << 3, mouse_release, content);
	mlx_hook(content->src.win, 6, 1L << 6, mouse_detection, content);
	mlx_loop_hook(content->src.mlx, draw_game, content);
	mlx_loop(content->src.mlx);
}
