#include "../../inc/cub3d.h"

void init_player(t_container *content)
{
    content->plr.up = 0;
    content->plr.down = 0;
    content->plr.left = 0;
    content->plr.right = 0;
}

void mlx_res_init(t_container *content)
{
    init_player(content);
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
        if (i < PLR / 3 || i > PLR / 1.5 )
        {
            print_pxt(content->plr.x + i,content->plr.y , 0x00FF00, content);
            print_pxt(content->plr.x + i,content->plr.y + 2 , 0x00FF00, content);
        }
        i++;
    }
    i = 0;
    while (i < PLR)
    {
        if (i < PLR / 3 || i > PLR / 1.5 )
        {
            print_pxt(content->plr.x, content->plr.y + i, 0x00FF00, content);
            print_pxt(content->plr.x + 2, content->plr.y + i, 0x00FF00, content);
        }
        i++;
    }
    i = 0;
    while (i < PLR)
    {
        if (i < PLR / 3 || i > PLR / 1.5 )
        {
            print_pxt(content->plr.x + i, content->plr.y + PLR - 1, 0x00FF00, content);
            print_pxt(content->plr.x + i, content->plr.y + PLR - 3, 0x00FF00, content);
        }
        i++;
    }
    i = 0;
    while (i < PLR)
    {
        if (i < PLR / 3 || i > PLR / 1.5)
        {
            print_pxt(content->plr.x + PLR - 1, content->plr.y + i, 0x00FF00, content);
            print_pxt(content->plr.x + PLR - 3, content->plr.y + i, 0x00FF00, content);
        }
        i++;
    }
    print_pxt(content->plr.x + (PLR - 0.5) / 2, content->plr.y + (PLR - 0.5) / 2, 0x00FF00, content);
    print_pxt(content->plr.x - 1 + (PLR - 0.5) / 2, content->plr.y + (PLR - 0.5) / 2, 0x00FF00, content);
    print_pxt(content->plr.x - 2 + (PLR - 0.5) / 2, content->plr.y + (PLR - 0.5) / 2, 0x00FF00, content);
    print_pxt(content->plr.x + 1 + (PLR - 0.5) / 2, content->plr.y + (PLR - 0.5) / 2, 0x00FF00, content);
    print_pxt(content->plr.x + 2 + (PLR - 0.5) / 2, content->plr.y + (PLR - 0.5) / 2, 0x00FF00, content);

    print_pxt(content->plr.x + (PLR - 0.5) / 2, content->plr.y - 1 + (PLR - 0.5) / 2, 0x00FF00, content);
    print_pxt(content->plr.x + (PLR - 0.5) / 2, content->plr.y - 2 + (PLR - 0.5) / 2, 0x00FF00, content);
    print_pxt(content->plr.x + (PLR - 0.5) / 2, content->plr.y + 1 + (PLR - 0.5) / 2, 0x00FF00, content);
    print_pxt(content->plr.x + (PLR - 0.5) / 2, content->plr.y + 2 + (PLR - 0.5) / 2, 0x00FF00, content);
}

// void drawing_plr(t_container *content)
// {
//     int r = PLR / 2;
//     int cx = content->plr.x + r;
//     int cy = content->plr.y + r;

//     double angle = 0.0;
//     double step = 0.01;

//     while (angle <= 2 * PI)
//     {
//         int x = (int)(cx + r * cos(angle));
//         int y = (int)(cy + r * sin(angle));
//         print_pxt(x, y, 0xFF0000, content);
//         angle += step;
//     }
// }


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
    int i = 0;
    int j;
    while (content->map[i])
    {
        j = 0;
        while (content->map[j])
        {
            if (content->map[i][j] == '1' || content->map[i][j] == ' ' || content->map[i][j] == '\t')
                draw_m(j * PIXEL_SIZE, i * PIXEL_SIZE, PIXEL_SIZE, 0xFF8C00, content);
            if (content->map[i][j] == '0' || content->map[i][j] == 'W' || content->map[i][j] == 'N' \
            || content->map[i][j] == 'E' || content->map[i][j] == 'S')
                draw_m(j * PIXEL_SIZE, i * PIXEL_SIZE, PIXEL_SIZE, 0x1f1200, content);
            j++;
        }
        i++;
    }
    return (0);
}

void clear_map_after_player(t_container *content)
{
    int x;
    int y;

    x = 0;
    while (x < content->map_w * PIXEL_SIZE)
    {
        y = 0;
        while (y < content->map_h * PIXEL_SIZE)
        {
            print_pxt(y, x, 0x000000, content);
            y++;
        }
        x++;
    }
}

int key_action(int keycode, t_container *content)
{
	if (keycode == 0)
		content->plr.left = 1;
	else if (keycode == 1)
		content->plr.down = 1;
	else if (keycode == 2)
		content->plr.right = 1;
	else if (keycode == 13)
		content->plr.up = 1;
	return (0);
}

int key_back(int keycode, t_container *content)
{
	if (keycode == 0)
		content->plr.left = 0;
	else if (keycode == 1)
		content->plr.down = 0;
	else if (keycode == 2)
		content->plr.right = 0;
	else if (keycode == 13)
		content->plr.up = 0;
	return (0);
}

void let_player_move(t_container *content)
{
    int speed;

    speed = 1;
    if (content->plr.up)
        content->plr.y -= speed;
    if (content->plr.down)
        content->plr.y += speed;
    if (content->plr.left)
        content->plr.x -= speed;
    if (content->plr.right)
        content->plr.x += speed;
}

int draw_game(t_container *content)
{
    let_player_move(content);
    clear_map_after_player(content);
    draw_map(content);
    drawing_plr(content);
    mlx_put_image_to_window(content->src.mlx, content->src.win, content->src.img, 0, 0);
    return (0);
}

void start_the_play(t_container *content)
{
    mlx_res_init(content);
    mlx_put_image_to_window(content->src.mlx, content->src.win, content->src.img, 0, 0);
    mlx_hook(content->src.win, 2, 1L<<0, key_action, content);
    mlx_hook(content->src.win, 3, 1L<<1, key_back, content);
    mlx_loop_hook(content->src.mlx, draw_game, content);
    mlx_loop(content->src.mlx);
}
