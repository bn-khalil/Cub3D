/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:11:56 by kben-tou          #+#    #+#             */
/*   Updated: 2025/06/28 13:13:53 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void ft_texture_loading(t_container *content, t_sprite *spr)
{
    if (content->sprite_switcher < 10)
        spr->img = mlx_xpm_file_to_image(content->src.mlx, \
        "./textures/h6.xpm", &spr->width, &spr->height);
    else if (content->sprite_switcher < 15)
        spr->img = mlx_xpm_file_to_image(content->src.mlx, \
        "./textures/h5.xpm", &spr->width, &spr->height);
    else if (content->sprite_switcher < 25)
        spr->img = mlx_xpm_file_to_image(content->src.mlx, \
        "./textures/h4.xpm", &spr->width, &spr->height);
    else if (content->sprite_switcher < 30)
        spr->img = mlx_xpm_file_to_image(content->src.mlx, \
        "./textures/h3+.xpm", &spr->width, &spr->height);
    else if (content->sprite_switcher < 35)
        spr->img = mlx_xpm_file_to_image(content->src.mlx, \
        "./textures/h1.xpm", &spr->width, &spr->height);
    else
    {
        if (content->plr.up)
            spr->img = mlx_xpm_file_to_image(content->src.mlx, \
            "./textures/h4.xpm", &spr->width, &spr->height);
        else
            spr->img = mlx_xpm_file_to_image(content->src.mlx, \
            "./textures/h2.xpm", &spr->width, &spr->height);
    }
    if (!spr->img)
        ft_error("failed loading image\n", content);
}

void put_texture_to_screen(t_container *content, t_sprite *spr)
{
    int y;
    int x;

    y = -1;
    spr->buffer = mlx_get_data_addr(spr->img, &spr->nbits, \
    &spr->size_l, &spr->endian);
    spr->draw_x = (MAP_W - (MAP_W / 5) - spr->width);
    spr->draw_y = MAP_H - spr->height + 8;
    while (++y < spr->height)
    {
        x = -1;
        while (++x < spr->width)
        {
            spr->color = ((unsigned int*)spr->buffer)[y * (spr->size_l / 4) + x];
            spr->px = spr->draw_x + x;
            spr->py = spr->draw_y + y;
            spr->rgb = spr->color & 0x00FFFFFF;
            if (spr->rgb != 0x000000)
            {
                if (spr->px >= 0 && spr->px < MAP_W \
                && spr->py >= 0 && spr->py < MAP_H)
                    print_pxt(spr->px, spr->py, spr->color, content);
            }
        }
    }
}

void draw_sprite_hands(t_container *content)
{
    t_sprite spr;

    ft_texture_loading(content, &spr);
    put_texture_to_screen(content, &spr);
    mlx_destroy_image(content->src.mlx, spr.img);
    ++content->sprite_switcher;
    if (content->sprite_switcher >= 450)
        content->sprite_switcher = 0;
}