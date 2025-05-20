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
void configue_rgb_parsing(t_container *content, char *color)
{
    int i;
    int pixel_ele;
    char **rgb = ft_split(color, ',');
    if (!rgb || !rgb[0])
        ft_error("Error: allocation failed!\n", content);
    i = 0;
    while (rgb[i])
    {
        if (i == 0)
            pixel_ele = ft_atoi(rgb[i] + 2);
        else
            pixel_ele = ft_atoi(rgb[i]);
        if (pixel_ele < 0 || pixel_ele > 255)
            ft_error("Error: color not valid!", content);
        i++;
    }
    // free rgb
}

void print_list(t_config *head) {
    t_config *current = head;
    while (current) {
        printf("ID: %s, Value: %s\n", current->id, current->value);
        current = current->next;
    }
}

void configure_parsing(t_container *content)
{
    int i;

    i = 0;
    while (content->configues[i])
    {
        if (ft_strncmp("NO ", content->configues[i], 3) == 0)
            configue_direction_parsing(content, ft_substr(content->configues[i], 0, 3), ft_substr(content->configues[i], 3, ft_strlen(content->configues[i])));
        else if (ft_strncmp("SO ", content->configues[i], 3) == 0)
            configue_direction_parsing(content, ft_substr(content->configues[i], 0, 3), ft_substr(content->configues[i], 3, ft_strlen(content->configues[i])));
        else if (ft_strncmp("WE ", content->configues[i], 3) == 0)
            configue_direction_parsing(content, ft_substr(content->configues[i], 0, 3), ft_substr(content->configues[i], 3, ft_strlen(content->configues[i])));
        else if (ft_strncmp("EA ", content->configues[i], 3) == 0)
            configue_direction_parsing(content, ft_substr(content->configues[i], 0, 3), ft_substr(content->configues[i], 3, ft_strlen(content->configues[i])));
        else if (ft_strncmp("F ", content->configues[i], 2) == 0)
            configue_rgb_parsing(content, content->configues[i]);
        else if (ft_strncmp("C ", content->configues[i], 2) == 0)
            configue_rgb_parsing(content, content->configues[i]);
        else
            ft_error("Error: missing or invalid identifier\n", content);
        i++;
    }
	print_list(content->confs);
}
