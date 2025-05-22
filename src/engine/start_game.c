#include "../../inc/cub3d.h"

void mlx_res_init(t_container *content)
{
    content->src.mlx = mlx_init();
    content->src.win = mlx_new_window(content->src.mlx, content->map_w * PIXEL_SIZE, content->map_h * PIXEL_SIZE, "Cub3D");
    content->src.img = mlx_new_image(content->src.win, content->map_w * PIXEL_SIZE, content->map_h * PIXEL_SIZE);
    content->src.buffer_pos = mlx_get_data_addr(content->src.img, &content->src.pixel_bits_number, &content->src.len_with_pixels, &content->src.endian);
}


void print_pxt(int x, int y, int color, t_container *content)
{
    int pos;

    if (x < 0 || x >= content->map_w || y < 0 || y >= content->map_h)
        return;
    pos = y * content->src.len_with_pixels + x * (content->src.pixel_bits_number / 8);
    content->src.buffer_pos[pos] = color & 0xFF;
    content->src.buffer_pos[pos + 1] = (color >> 8) & 0xFF;
    content->src.buffer_pos[pos + 2] = (color >> 16) & 0xFF;
}

void drawing_plr(t_container *content)
{
    int i = 0;

    // Log to confirm correct values
    printf("Player pixel coords: x = %d, y = %d\n", content->plr.x, content->plr.y);

    while (i < PLR)
    {
        // print_pxt(content->plr.x + i, content->plr.y, 0xFFFFFF, content);
        mlx_pixel_put(content->src.mlx, content->src.win ,content->plr.x, content->plr.y, 0xFFFFFF);
        i++;
    }
}


void start_the_play(t_container *content)
{
    mlx_res_init(content);
    drawing_plr(content);
    mlx_put_image_to_window(content->src.mlx, content->src.win, content->src.img, 0, 0);
    mlx_loop(content->src.mlx);
}