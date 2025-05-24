#include "../../inc/cub3d.h"

void init_player(t_container *content)
{
    content->plr.up = 0;
    content->plr.down = 0;
    content->plr.left = 0;
    content->plr.right = 0;
    content->plr.speed = 3;
	if (content->player_pos == 'E')
	    content->plr.r_angle = 0;
	if (content->player_pos == 'W')
		content->plr.r_angle = PI;
	if (content->player_pos == 'S')
		content->plr.r_angle = PI / 2;
    if (content->player_pos == 'N')
		content->plr.r_angle = 3 * PI / 2;
    content->plr.r_speed = 2  * (PI / 180);
}

void mlx_res_init(t_container *content)
{
    init_player(content);
    content->src.mlx = mlx_init();
    content->src.win = mlx_new_window(content->src.mlx, content->map_w * PIXEL_SIZE, content->map_h * PIXEL_SIZE, "Cub3D");
    content->src.img = mlx_new_image(content->src.mlx, content->map_w * PIXEL_SIZE, content->map_h * PIXEL_SIZE);
    content->src.buffer_pos = mlx_get_data_addr(content->src.img, &content->src.pixel_bits_number, &content->src.len_with_pixels, &content->src.endian);
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

int ft_close(t_container *content)
{
    // free and close window and mlx connections 
    (void)content;
    exit(0);
    return (0);
}

int key_back(int keycode, t_container *content)
{
    if (keycode == 53)
		ft_close(content);
	else if (keycode == 0)
		content->plr.left = 0;
	else if (keycode == 1)
		content->plr.down = 0;
	else if (keycode == 2)
		content->plr.right = 0;
	else if (keycode == 13)
		content->plr.up = 0;
	return (0);
}

int is_wall(float x, float y, t_container *content)
{
    int i;
    int j;

    // if (x < 0 || y < 0 || x >= content->map_w || y >= content->map_h)
    //     return (1);
    i = x / PIXEL_SIZE;
    j = y / PIXEL_SIZE;
    if (i < 0 || j < 0 || i >= content->map_w || j >= content->map_h)
        return 1;
    if (content->map[j][i] == '1')
        return (1);
    return (0);
}

int ft_is_collision(float x, float y, t_container *content)
{
    if (is_wall(x, y, content))
        return 1;
    if (is_wall(x + PLR, y, content))
        return 1;
    if (is_wall(x, y, content))
        return 1;
    if (is_wall(x, y + PLR, content))
        return 1;
    if (is_wall(x, y, content))
        return 1;
    return 0;
}

void let_player_move(t_container *content)
{

    float x;
    float y;
    
    x = 0;
    y = 0;
    if (content->plr.left)
        content->plr.r_angle -= content->plr.r_speed;
    if (content->plr.right)
        content->plr.r_angle += content->plr.r_speed;
    if (content->plr.r_angle < 0)
        content->plr.r_angle += 2 * PI;
    if (content->plr.r_angle > 2 * PI)
        content->plr.r_angle -= 2 * PI;
    if (content->plr.up)
    {
        x = content->plr.x + cos(content->plr.r_angle) * content->plr.speed;
        y = content->plr.y + sin(content->plr.r_angle) * content->plr.speed;
        if (!ft_is_collision(x, y, content))
        {
            content->plr.x = x;
            content->plr.y = y;
        }
    }
    if (content->plr.down)
    {
        x = content->plr.x - cos(content->plr.r_angle) * content->plr.speed;
        y = content->plr.y - sin(content->plr.r_angle) * content->plr.speed;
        if (!ft_is_collision(x, y, content))
        {
            content->plr.x = x;
            content->plr.y = y;
        }
    }
}


void drawing_rays_angle(t_container *content)
{
    float ray_x = content->plr.x + PLR / 2;
    float ray_y = content->plr.y + PLR / 2;
    float cos_an = cos(content->plr.r_angle);
    float sin_an = sin(content->plr.r_angle);

    while (is_wall(ray_x, ray_y, content) == 0)
    {
        print_pxt(ray_x, ray_y, 0x00FF00, content);
        ray_x += cos_an;
        ray_y += sin_an;
    }
}

int draw_game(t_container *content)
{
    let_player_move(content);
    clear_map_after_player(content);
    draw_map(content);
    drawing_plr(content);
    drawing_rays_angle(content);
    mlx_put_image_to_window(content->src.mlx, content->src.win, content->src.img, 0, 0);
    return (0);
}

void start_the_play(t_container *content)
{
    mlx_res_init(content);
    draw_map(content);
    mlx_put_image_to_window(content->src.mlx, content->src.win, content->src.img, 0, 0);
    mlx_hook(content->src.win, 17, 0, ft_close, content);
    mlx_hook(content->src.win, 2, 1L<<0, key_action, content);
    mlx_hook(content->src.win, 3, 1L<<1, key_back, content);
    mlx_loop_hook(content->src.mlx, draw_game, content);
    mlx_loop(content->src.mlx);
}
