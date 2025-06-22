/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plr_moving.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:56:34 by sait-nac          #+#    #+#             */
/*   Updated: 2025/06/21 22:42:16 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

float fix_angle(float angle)
{
    angle = fmod(angle, 2 * PI);
    if (angle < 0)
        angle += 2 * PI;
    return angle;
}

int is_wall(float x, float y, t_container *content) {
    int i = (int)(x / PIXEL_SIZE);
    int j = (int)(y / PIXEL_SIZE);

    if (i < 0 || j < 0 || i >= content->map_w || j >= content->map_h)
        return 1;

    if (!content->map || !content->map[j])
        return 1;

    if (content->map[j][i] && (content->map[j][i] == '1' || content->map[j][i] == 'D'))
        return 1;

    return 0;
}

int ft_is_collision(float x, float y, t_container *content) {
    float offsets[4][2]; // Declaration by itself

    offsets[0][0] = -PLR; // Initialization separate
    offsets[0][1] = -PLR;
    offsets[1][0] = PLR;
    offsets[1][1] = -PLR;
    offsets[2][0] = -PLR;
    offsets[2][1] = PLR;
    offsets[3][0] = PLR;
    offsets[3][1] = PLR;

    int i = 0; // This declaration is fine as is

    while (i < 4) {
        if (is_wall(x + offsets[i][0], y + offsets[i][1], content)) {
            return 1; // Collision detected
        }
        i++;
    }
    return 0; // No collision
}

void let_player_move(t_container *content)
{
    content->plr.r_angle = fix_angle(content->plr.r_angle);

    if (content->plr.rotate_left)
        content->plr.r_angle -= content->plr.r_speed;
    if (content->plr.rotate_right)
        content->plr.r_angle += content->plr.r_speed;

    content->plr.r_angle = fix_angle(content->plr.r_angle);

    float cos_an = cos(content->plr.r_angle);
    float sin_an = sin(content->plr.r_angle);

    if (fabs(cos_an) < 0.0001) 
        cos_an = 0;
    if (fabs(sin_an) < 0.0001) 
        sin_an = 0;

    float new_x = content->plr.x;
    float new_y = content->plr.y;

    if (content->plr.up) {
        new_x = content->plr.x + cos_an * content->plr.speed;
        new_y = content->plr.y + sin_an * content->plr.speed;
        if (!ft_is_collision(new_x, new_y, content)) {
            content->plr.x = new_x;
            content->plr.y = new_y;
        }
    }
    if (content->plr.down) {
        new_x = content->plr.x - cos_an * content->plr.speed;
        new_y = content->plr.y - sin_an * content->plr.speed;
        if (!ft_is_collision(new_x, new_y, content)) {
            content->plr.x = new_x;
            content->plr.y = new_y;
        }
    }
    if (content->plr.left) {
        new_x = content->plr.x + sin_an * content->plr.speed;
        new_y = content->plr.y - cos_an * content->plr.speed;
        if (!ft_is_collision(new_x, new_y, content)) {
            content->plr.x = new_x;
            content->plr.y = new_y;
        }
    }
    if (content->plr.right) {
        new_x = content->plr.x - sin_an * content->plr.speed;
        new_y = content->plr.y + cos_an * content->plr.speed;
        if (!ft_is_collision(new_x, new_y, content)) {
            content->plr.x = new_x;
            content->plr.y = new_y;
        }
    }
}
