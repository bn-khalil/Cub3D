#include "../../inc/cub3d.h"

int ft_close(t_container *content) {
    ft_free_all(content);
    exit(0);
    return 0;
}
