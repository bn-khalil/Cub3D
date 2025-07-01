/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plr_moving.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:56:34 by sait-nac          #+#    #+#             */
/*   Updated: 2025/07/01 10:58:04 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void up_down(t_container *content, float cos_an, float sin_an)
{
    float new_x = content->plr.x;
    float new_y = content->plr.y;

    if (content->plr.up) 
    {
        new_x = content->plr.x + cos_an * content->plr.speed;
        new_y = content->plr.y + sin_an * content->plr.speed;
        if (!ft_is_collision(new_x, new_y, content)) 
            updated_x_y(content, new_x, new_y);
    }
    if (content->plr.down) 
    {
        new_x = content->plr.x - cos_an * content->plr.speed;
        new_y = content->plr.y - sin_an * content->plr.speed;
        if (!ft_is_collision(new_x, new_y, content)) 
            updated_x_y(content, new_x, new_y);
    }

}

void left_right(t_container *content, float cos_an, float sin_an)
{
    float new_x = content->plr.x;
    float new_y = content->plr.y;

    if (content->plr.left) 
    {
        new_x = content->plr.x + sin_an * content->plr.speed;
        new_y = content->plr.y - cos_an * content->plr.speed;
        if (!ft_is_collision(new_x, new_y, content)) 
            updated_x_y(content, new_x, new_y);
    }
    if (content->plr.right) 
    {
        new_x = content->plr.x - sin_an * content->plr.speed;
        new_y = content->plr.y + cos_an * content->plr.speed;
        if (!ft_is_collision(new_x, new_y, content)) 
            updated_x_y(content, new_x, new_y);
    }

}

void let_player_move(t_container *content)
{
    float cos_an = cos(content->plr.r_angle);
    float sin_an = sin(content->plr.r_angle);

    content->plr.r_angle = fix_angle(content->plr.r_angle);
    if (content->plr.rotate_left)
        content->plr.r_angle -= content->plr.r_speed;
    if (content->plr.rotate_right)
        content->plr.r_angle += content->plr.r_speed;
    content->plr.r_angle = fix_angle(content->plr.r_angle);
    if (fabs(cos_an) < 0.0001) 
        cos_an = 0;
    if (fabs(sin_an) < 0.0001) 
        sin_an = 0;
    up_down(content, cos_an, sin_an);
    left_right(content, cos_an, sin_an);
}
