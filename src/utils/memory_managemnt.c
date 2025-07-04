/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_managemnt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:23:16 by kben-tou          #+#    #+#             */
/*   Updated: 2025/07/03 14:56:44 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_close(t_container *content)
{
	ft_free_all(content);
	exit(0);
	return (0);
}

void	ft_free_2d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static void	ft_close_configs(t_container *content)
{
	t_config	*tmp;

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

void	ft_free_all(t_container *content)
{
	close(content->fd_map);
	free(content->rays);
	ft_free_2d(content->file_content);
	ft_free_2d(content->map);
	ft_close_configs(content);
}

void	ft_error(char *err, t_container *content)
{
	write(2, err, ft_strlen(err));
	if (!content)
		exit(1);
	ft_free_all(content);
	exit(1);
}
