#include "../../inc/cub3d.h"

void print_pxt(int x, int y, int color, t_container *content)
{
    char *pos;
    if (x >= 0 && x < MAP_W && y >= 0 && y < MAP_H) {
        pos = content->src.buffer_pos + y * content->src.len_with_pixels + x * (content->src.pixel_bits_number / 8);
        *(unsigned int *)pos = color;
    }
}

void drawLineDDA(int x0, int y0, int x1, int y1, int color, t_container *content) 
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = x0;
    float y = y0;
    int i = 0;

    while (i <= steps) {
        print_pxt((int)round(x) * MAP_RATIO, (int)round(y) * MAP_RATIO, color, content);
        x += xInc;
        y += yInc;
        i++;
    }
}
