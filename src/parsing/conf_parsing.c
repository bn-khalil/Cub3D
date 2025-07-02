#include "../../inc/cub3d.h"

int	is_paces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	check_conf_duplication(t_container *content)
{
	int	i;
	int	j;

	i = 0;
	while (content->configues[i])
	{
		if (is_paces(content->configues[i]))
		{
			i++;
			continue ;
		}
		j = i + 1;
		while (content->configues[j])
		{
			if (is_paces(content->configues[j]))
				;
			else if (ft_strcmp(content->configues[i],
					content->configues[j]) == 0)
				ft_error("Error: duplicated configue line\n", content);
			j++;
		}
		i++;
	}
}

int	get_directions_with_path(t_container *content,
			int *i, int *texture_count)
{
	if (ft_strncmp("NO ", content->configues[*i], 3) == 0
		|| ft_strncmp("SO ", content->configues[*i], 3) == 0
		|| ft_strncmp("WE ", content->configues[*i], 3) == 0
		|| ft_strncmp("EA ", content->configues[*i], 3) == 0)
	{
		configue_direction_parsing(content,
			ft_substr(content->configues[*i], 0, 3),
			ft_substr(content->configues[*i], 3,
				ft_strlen(content->configues[*i])));
		(*texture_count)++;
		return (1);
	}
	return (0);
}

void	get_floor_ceilling_rgb(t_container *content,
			int *i, int flag, int *colors_count)
{
	configue_rgb_parsing(content, content->configues[*i], flag);
	(*colors_count)++;
}

void	configure_parsing(t_container *content)
{
	int	i;
	int	texture_count;
	int	colors_count;

	i = 0;
	texture_count = 0;
	colors_count = 0;
	check_conf_duplication(content);
	while (content->configues[i])
	{
		if (get_directions_with_path(content, &i, &texture_count) == 1)
			;
		else if (ft_strncmp("F ", content->configues[i], 2) == 0)
			get_floor_ceilling_rgb(content, &i, 1, &colors_count);
		else if (ft_strncmp("C ", content->configues[i], 2) == 0)
			get_floor_ceilling_rgb(content, &i, 0, &colors_count);
		else if (is_paces(content->configues[i]))
			;
		else
			ft_error("Error: missing or invalid identifier!\n", content);
		i++;
	}
	if (texture_count != 4 || colors_count != 2)
		ft_error("Error: missing or duplicated configes!\n", content);
}
