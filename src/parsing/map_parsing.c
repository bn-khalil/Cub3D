/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:57:05 by kben-tou          #+#    #+#             */
/*   Updated: 2025/07/03 14:57:06 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_map_covered_with_walls(int x, int y, t_container *content)
{
	if (x < 0 || x >= ft_strlen(content->map[y])
		|| y < 0 || y >= content->map_h)
		return (0);
	if (x - 1 < 0 || y - 1 < 0)
		return (0);
	if (content->map[y - 1][x] == ' '
		|| content->map[y - 1][x] == '\t'
		|| content->map[y + 1][x] == ' '
		|| content->map[y + 1][x] == '\t')
		return (1);
	if (content->map[y][x - 1] == ' '
		|| content->map[y][x - 1] == '\t'
		|| content->map[y][x + 1] == ' '
		|| content->map[y][x + 1] == '\t')
		return (1);
	if (x >= ft_strlen(content->map[y - 1])
		|| x >= ft_strlen(content->map[y + 1]))
		return (1);
	return (0);
}

void	check_map_components(t_container *content)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	count = 0;
	while (content->map[i])
	{
		j = 0;
		if (content->map[i][0] == '\0')
			count++;
		while (content->map[i][j])
		{
			player_pos_check(content, i, j);
			map_sides_check(content, i, j);
			map_items_check(content, i, j);
			j++;
		}
		i++;
	}
	if (!content->player_pos)
		ft_error("Error: map doesn't have player\n", content);
}

void	complete_map_rows(t_container *content)
{
	int	i;

	i = 0;
	while (content->map[i])
	{
		content->map[i] = ft_complete(content, content->map[i]);
		i++;
	}
}

void	parsing_map_content(t_container *content, int start)
{
	int	i;
	int	j;

	i = 0;
	while (content->file_content[start + i])
		i++;
	content->map = malloc(sizeof(char *) * (i + 1));
	if (!content->map)
		ft_error("Error: allocation failed!\n", content);
	i = -1;
	while (content->file_content[start + (++i)])
	{
		j = start + i;
		while (content->file_content[j] && is_paces(content->file_content[j]))
			j++;
		if (content->file_content[j] == NULL)
			break ;
		content->map[i] = ft_strdup(content->file_content[start + i]);
	}
	content->map[i] = NULL;
	if (!content->map || !content->map[0])
		ft_error("Error: the map isn't exist!\n", content);
	get_width_and_height(content);
	complete_map_rows(content);
	check_map_components(content);
}
