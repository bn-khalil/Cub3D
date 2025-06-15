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

    if (content->map[j][i] == '1' || content->map[j][i] == 'D')
        return 1;

    return 0;
}

int ft_is_collision(float x, float y, t_container *content) {
    if (is_wall(x, y, content) || 
        is_wall(x + (float)PLR, y, content) ||
        is_wall(x, y + (float)PLR, content) ||
        is_wall(x + (float)PLR, y + (float)PLR, content)) {
        return 1;
    }
    return 0;
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
