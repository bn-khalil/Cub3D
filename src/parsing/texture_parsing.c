#include "../../inc/cub3d.h"

 void	ft_configue(t_config **lst, t_config *new)
{
	t_config	*head;

	if (!lst || !new)
		return ;
	if (*lst != NULL)
	{
		head = *lst;
		while (head->next != NULL)
			head = head->next;
		head->next = new;
	}
	else
		*lst = new;
}

t_config	*ft_new_config(t_container *content, int fd_file, char *dir, char *path)
{
	t_config	*head;

	head = malloc(sizeof(t_config));
	if (!head)
		ft_error("Error: allocations failed", content);
	head->id = dir;
	head->value = path;
	head->fd = fd_file;
	head->next = NULL;
	return (head);
}

void configue_direction_parsing(t_container *content, char *direction, char *path)
{
	ft_configue(&content->confs, ft_new_config(content, 0, direction, path));
}

void print_list(t_config *head)
{
    t_config *current = head;
    while (current) {
        printf("ID: %s, Value: %s\n", current->id, current->value);
        current = current->next;
    }
}