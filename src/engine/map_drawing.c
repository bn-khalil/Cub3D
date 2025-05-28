#include "../../inc/cub3d.h"

void draw_m(int x, int y, int color, t_container *content)
{
    int i = 0;
    int j;
    while (i < PIXEL_SIZE - 1)
    {
        j = 0;
        while (j < PIXEL_SIZE - 1)
        {
            print_pxt(x + i, y + j, color, content);
            j++;
        }
        i++;
    }
}

int draw_map(t_container *content)
{
    int i = 0;
    int j;
    while (content->map[i])
    {
        j = 0;
        while (content->map[j])
        {
            if (content->map[i][j] == '1' || content->map[i][j] == ' ' || content->map[i][j] == '\t')
                draw_m(j * PIXEL_SIZE * MAP_RATIO , i * PIXEL_SIZE * MAP_RATIO, 0xFF8C00, content);
            if (content->map[i][j] == '0' || content->map[i][j] == 'W' || content->map[i][j] == 'N' \
            || content->map[i][j] == 'E' || content->map[i][j] == 'S')
                draw_m(j * PIXEL_SIZE * MAP_RATIO, i * PIXEL_SIZE * MAP_RATIO, 0x1f1200, content);
            j++;
        }
        i++;
    }
    return (0);
}

void draw_clean(int x, int y, int color, t_container *content)
{
    int i = 0;
    int j;
    while (i < PIXEL_SIZE)
    {
        j = 0;
        while (j < PIXEL_SIZE)
        {
            print_pxt(x + i, y + j, color, content);
            j++;
        }
        i++;
    }
}

void clear_map_after_player(t_container *content)
{
    int x;
    int y;

    y = 0;
    while (y < content->map_h)
    { 
        x = 0;
        while (x < content->map_w)
        {
            draw_clean(x * PIXEL_SIZE, y * PIXEL_SIZE, 0x000000, content);
            x++;
        }
        y++;
    }
}
