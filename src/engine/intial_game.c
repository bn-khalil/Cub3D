#include "../../inc/cub3d.h"

void init_player(t_container *content) {
    content->plr.up = 0;
    content->plr.down = 0;
    content->plr.left = 0;
    content->plr.right = 0;
    content->plr.speed =3.0;
    content->plr.rotate_left = 0;
    content->plr.rotate_right = 0;
    content->num_rays = (content->map_w * PIXEL_SIZE) / WALL_COL_WIDH;
    content->rays = malloc(sizeof(t_ray) * content->num_rays);
    ft_memset(content->rays, 0, sizeof(t_ray) * content->num_rays);
    
    if (content->plr.std_direction == 'E')
        content->plr.r_angle = 0;
    if (content->plr.std_direction == 'W')
        content->plr.r_angle = PI;
    if (content->plr.std_direction == 'N')
        content->plr.r_angle = PI / 2;
    if (content->plr.std_direction == 'S')
        content->plr.r_angle = 3 * PI / 2;
    
    content->plr.r_speed = 3 * (PI / 180);  
}

void mlx_res_init(t_container *content) {
    init_player(content);
    content->src.mlx = mlx_init();
    content->src.win = mlx_new_window(content->src.mlx, content->map_w * PIXEL_SIZE, 
                                     content->map_h * PIXEL_SIZE, "Cub3D");
    content->src.img = mlx_new_image(content->src.mlx, content->map_w * PIXEL_SIZE, 
                                    content->map_h * PIXEL_SIZE);
    content->src.buffer_pos = mlx_get_data_addr(content->src.img, 
                                              &content->src.pixel_bits_number, 
                                              &content->src.len_with_pixels, 
                                              &content->src.endian);
    texture_init(content);
}
void start_the_play(t_container *content) {
    mlx_res_init(content);
    /* draw_map(content); */
    mlx_put_image_to_window(content->src.mlx, content->src.win, content->src.img, 0, 0);
    mlx_hook(content->src.win, 17, 0, ft_close, content);
    mlx_hook(content->src.win, 2, 1L << 0, key_action, content);
    mlx_hook(content->src.win, 3, 1L << 1, key_back, content);
    mlx_loop_hook(content->src.mlx, draw_game, content);
    mlx_loop(content->src.mlx);
}
