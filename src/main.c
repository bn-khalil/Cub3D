/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:00:23 by kben-tou          #+#    #+#             */
/*   Updated: 2025/07/06 08:29:38 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	is_file_ext_valid(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len >= 4)
	{
		if (ft_strcmp(filename + (len - 4), ".cub") != 0)
			ft_error("there is not file with this name \n", NULL);
	}
	else
		ft_error("invalid file name!\n", NULL);
}

void	check_fd(t_container *content, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error("loading sprite failed!\n", content);
	else
		close(fd);
}

void	check_sprite_files(t_container *content)
{
	check_fd(content, "./textures/h1.xpm");
	check_fd(content, "./textures/h2.xpm");
	check_fd(content, "./textures/h3+.xpm");
	check_fd(content, "./textures/h4.xpm");
	check_fd(content, "./textures/h5.xpm");
	check_fd(content, "./textures/h6.xpm");
}

int	main(int ac, char **av)
{
	t_container	content;

	if (ac != 2)
		return (write(2, "Invalid number of arrguments!\n", 31), 1);
	is_file_ext_valid(av[1]);
	ft_memset(&content, 0, sizeof(t_container));
	content.filename = av[1];
	get_and_init_map(&content);
	check_sprite_files(&content);
	start_the_play(&content);
	ft_free_all(&content);
	return (0);
}
