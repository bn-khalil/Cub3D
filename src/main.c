#include "../inc/cub3d.h"

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

void ft_close_configs(t_container *content)
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

void is_file_ext_valid(char *filename) {
  int len;

  len = ft_strlen(filename);
  if (len >= 4) {
    if (ft_strcmp(filename + len - 4, ".cub") != 0)
      ft_error("there is not file with this name \n", NULL);
  } else
    ft_error("invalid file name", NULL);
}

void f()
{
  system(" leak cub3d ");
}
int main(int ac, char **av) {
  t_container content;

  atexit(f);
  if (ac != 2)
    return (write(2, "Invalid number of arrguments!\n", 31), 1);
  is_file_ext_valid(av[1]);
  ft_memset(&content, 0, sizeof(t_container));
  content.filename = av[1];
  get_and_init_map(&content);
  start_the_play(&content);
  ft_free_all(&content);
  return (0);
}
