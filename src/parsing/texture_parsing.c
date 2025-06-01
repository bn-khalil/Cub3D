#include "../../inc/cub3d.h"

void ft_configue(t_config **lst, t_config *new) {
  t_config *head;

  if (!lst || !new)
    return;
  if (*lst != NULL) {
    head = *lst;
    while (head->next != NULL)
      head = head->next;
    head->next = new;
  } else
    *lst = new;
}

t_config *ft_new_config(t_container *content, int fd_file, char *dir,
                        char *path) {
  t_config *head;

  head = malloc(sizeof(t_config));
  if (!head)
    ft_error("Error: allocations failed", content);
  head->id = dir;
  head->value = path;
  head->fd = fd_file;
  head->img = NULL;
  head->next = NULL;
  return (head);
}

int is_texture_valid(t_container *content, char *path) {
  int fd;

  fd = -1;
  fd = open(path, O_RDONLY);
  /* if (fd < 0) */
  /* 	ft_error("Erorr: texture file not valid!\n", content); */
  return (fd);
}

void configue_direction_parsing(t_container *content, char *direction, char *path)
{
	char *texture_path;

	texture_path = ft_strtrim(path, " \t");
	ft_configue(&content->confs, ft_new_config(content, \
	is_texture_valid(content, texture_path), direction, texture_path));
}

// void print_list(t_config *head)
// {
//     t_config *current = head;
//     while (current)
// 	{
// 		printf("%ss\n", current->id);
// 		if (ft_strcmp("EA ", current->id) == 0 || ft_strcmp("NO ",
// current->id) == 0 || ft_strcmp("WE ", current->id) == 0 || ft_strcmp("SO ",
// current->id) == 0)
//         	current = current->next;
// 		else
// 			ft_error("Error: missing textures!\n", NULL);
//     }
// }
