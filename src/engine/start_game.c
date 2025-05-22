#include "../../inc/cub3d.h"

void mlx_res_init(t_container *content)
{
    content->src.mlx = mlx_init();
    content->src.win = mlx_new_window(content->src.mlx, content->map_w * PIXEL_SIZE, content->map_h * PIXEL_SIZE, "Cub3D");
    content->src.img = mlx_new_image(content->src.mlx, content->map_w * PIXEL_SIZE, content->map_h * PIXEL_SIZE);
    content->src.buffer_pos = mlx_get_data_addr(content->src.img, &content->src.pixel_bits_number, &content->src.len_with_pixels, &content->src.endian);
}

void print_pxt(int x, int y, int color, t_container *content)
{
    char *pos;

    pos = content->src.buffer_pos + y * content->src.len_with_pixels + x * (content->src.pixel_bits_number / 8);
	*(unsigned int *)pos = color;
}

void drawing_plr(t_container *content)
{
    int i = 0;

    while (i < PLR)
    {
        print_pxt(content->plr.x + i,content->plr.y , 0xFFFFFF, content);
        i++;
    }
    i = 0;
    while (i < PLR)
    {
        print_pxt(content->plr.x, content->plr.y + i, 0xFFFFFF, content);
        i++;
    }
    i = 0;
    while (i < PLR)
    {
        print_pxt(content->plr.x + i, content->plr.y + PLR - 1, 0xFFFFFF, content);
        i++;
    }
    i = 0;
    while (i < PLR)
    {
        print_pxt(content->plr.x + PLR - 1, content->plr.y + i, 0xFFFFFF, content);
        i++;
    }
}

void draw_m(int x, int y, int size, int color, t_container *content)
{
    int i = 0;
    int j;
    while (i < size - 1)
    {
        j = 0;
        while (j < size - 1)
        {
            print_pxt(x + i, y + j, color, content);
            j++;
        }
        i++;
    }
}

int draw_map(t_container *content)
{
    int color = 0xFFF;
    int i = 0;
    int j;
    while (content->map[i])
    {
        j = 0;
        while (content->map[j])
        {
            if (content->map[i][j] == '1' || content->map[i][j] == ' ' || content->map[i][j] == '\t')
                draw_m(j * PIXEL_SIZE, i * PIXEL_SIZE, PIXEL_SIZE, color, content);
            if (content->map[i][j] == '0' || content->map[i][j] == 'W' || content->map[i][j] == 'N' || content->map[i][j] == 'E' || content->map[i][j] == 'S')
                draw_m(j * PIXEL_SIZE, i * PIXEL_SIZE, PIXEL_SIZE, 0x333, content);
            j++;
        }
        i++;
    }
    return (0);
}

int draw_game(t_container *content)
{
    draw_map(content);
    drawing_plr(content);
    mlx_put_image_to_window(content->src.mlx, content->src.win, content->src.img, 0, 0);
    return (0);
}

void start_the_play(t_container *content)
{
    mlx_res_init(content);
    mlx_put_image_to_window(content->src.mlx, content->src.win, content->src.img, 0, 0);
    mlx_loop_hook(content->src.mlx, draw_game, content);
    mlx_loop(content->src.mlx);
}
