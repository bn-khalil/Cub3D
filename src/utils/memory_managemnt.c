#include "../../inc/cub3d.h"

int ft_close(t_container *content) 
{
    ft_free_all(content);
    exit(0);
    return 0;
}

void	ft_free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
  free(str);
}

static void ft_close_configs(t_container *content)
{
  t_config *tmp;

  tmp = NULL;
  while (content->confs)
  {
    free(content->confs->value);
    free(content->confs->id);
    close(content->confs->fd);
    if (content->confs->img)
      mlx_destroy_image(content->src.mlx, content->confs->img);
    tmp = content->confs->next;
    free(content->confs);
    content->confs = tmp;
  }
}

void ft_free_all(t_container *content)
{
  close(content->fd_map);
  free(content->rays);
  ft_free_2d(content->file_content);
  ft_free_2d(content->map);
  ft_close_configs(content);
}

void ft_error(char *err, t_container *content)
{
  if (!content)
    return ;
  ft_free_all(content);
  write(2, err, ft_strlen(err));
  exit(1);
}