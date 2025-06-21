#include "../../inc/cub3d.h"

void texture_init(t_container *content)
{
    t_config *iter;
    int i = 0;

    if (!content || !content->src.mlx)
        ft_error("Error: MLX not initialized", content);

    iter = content->confs;
    while (iter)
    {
        if (!iter->value)
            ft_error("Error: texture path is NULL", content);
        iter->img = mlx_xpm_file_to_image(content->src.mlx, iter->value, &iter->txr_w, &iter->txr_h);
        if (!iter->img)
            ft_error("Error: failed to load texture image", content);
        iter->buffer_pos = mlx_get_data_addr(iter->img, &iter->pixel_bits_number, &iter->len_with_pixels, &iter->endian);
        if (!iter->buffer_pos)
            ft_error("Error: failed to get texture buffer", content);
        i++;
        iter = iter->next;
    }
}
