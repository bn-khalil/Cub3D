#include "../../inc/cub3d.h"

void start_the_play(t_container *content)
{
    t_src src;

    src.mlx = mlx_init();
    src.win = mlx_new_window(src.mlx, content->map_w * PIXEL_SIZE, content->map_h * PIXEL_SIZE, "Cub3D");
    src.img = mlx_new_image(src.win, content->map_w * PIXEL_SIZE, content->map_h * PIXEL_SIZE);
    
    mlx_loop(src.mlx);
}