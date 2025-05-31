#include "../inc/cub3d.h"

void ft_error(char *err, t_container *content) {
  (void)content;
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

void init_container(t_container *content, char *filename) {
  content->file_content = NULL;
  content->map = NULL;
  content->fd_map = -1;
  content->filename = filename;
  content->line = NULL;
  content->confs = NULL;
  content->ceiling_color = NULL;
  content->floor_color = NULL;
  content->player_pos = 0;
}

int main(int ac, char **av) {
  t_container content;

  if (ac != 2)
    return (write(2, "Invalid number of arrguments!\n", 31), 1);
  is_file_ext_valid(av[1]);
  init_container(&content, av[1]);
  get_and_init_map(&content);
  start_the_play(&content);
  return (0);
}
