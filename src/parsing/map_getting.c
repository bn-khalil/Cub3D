/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_getting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:57:10 by kben-tou          #+#    #+#             */
/*   Updated: 2025/07/03 14:57:11 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_is_wall(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '\t'
			&& str[i] != ' ' && str[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

int	get_conf_lines(t_container *content)
{
	int	i;

	i = 0;
	while (content->file_content[i] && !ft_is_wall(content->file_content[i]))
		i++;
	return (i);
}

void	saperate_map_configues(t_container *content)
{
	int	i;
	int	len;

	len = get_conf_lines(content);
	content->configues = malloc(sizeof(char *) * (len + 1));
	if (!content->configues)
		ft_error("allocation failed!\n", content);
	i = 0;
	while (i < len)
	{
		content->configues[i] = content->file_content[i];
		i++;
	}
	content->configues[len] = NULL;
	configure_parsing(content);
	parsing_map_content(content, len);
}

void	get_and_init_map(t_container *content)
{
	content->fd_map = open(content->filename, O_RDONLY);
	if (content->fd_map <= 0)
		ft_error("Error opning map file\n", content);
	content->file_content = ft_split(get_next_line(content), '\n', 0);
	if (!content->file_content || !content->file_content[0])
		ft_error("Error in map maybe empty\n", content);
	saperate_map_configues(content);
}
