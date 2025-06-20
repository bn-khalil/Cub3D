#include "../../inc/cub3d.h"

void print_pxt(int x, int y, int color, t_container *content)
{
    char *pos;
    if (x >= 0 && x < MAP_W && y >= 0 && y < MAP_H) {
        pos = content->src.buffer_pos + y * content->src.len_with_pixels + x * (content->src.pixel_bits_number / 8);
        *(unsigned int *)pos = color;
    }
}
