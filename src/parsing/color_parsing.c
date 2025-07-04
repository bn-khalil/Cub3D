/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:57:22 by kben-tou          #+#    #+#             */
/*   Updated: 2025/07/03 14:57:23 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	check_rgb_format(char *str, t_container *content)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		ft_error("Error: invalid rgb formatte!\n", content);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			ft_error("Error: invalid rgb formatte!\n", content);
		i++;
	}
}

void	check_color_separator(char *color_form, t_container *content)
{
	int	i;

	i = 0;
	while (color_form[i])
	{
		if (color_form[i] == ','
			&& (!ft_isdigit(color_form[i + 1])
				|| !ft_isdigit(color_form[i - 1])))
			ft_error("Error: color rgb not valid!\n", content);
		i++;
	}
}

char	**get_rgb_string(t_container *content, char *color)
{
	char	*color_form;
	char	*skeep_spaces;
	char	**rgb;

	color_form = ft_substr(color, 2, ft_strlen(color));
	skeep_spaces = ft_strtrim(color_form, " \t");
	if (!color_form || !skeep_spaces)
		ft_error("Error: color rgb not valid!\n", content);
	check_color_separator(skeep_spaces, content);
	rgb = ft_split(skeep_spaces, ',', 1);
	if (!rgb)
		ft_error("Error: allocation failed!\n", content);
	return (rgb);
}

void	configue_rgb_parsing(t_container *content, char *color, int flag)
{
	int				i;
	long			pixel_ele;
	char			**rgb;
	unsigned int	hex_color;
	unsigned int	rgb_int[3];

	rgb = get_rgb_string(content, color);
	i = 0;
	while (rgb[i])
	{
		check_rgb_format(rgb[i], content);
		pixel_ele = ft_atoi(rgb[i]);
		if (pixel_ele < 0 || pixel_ele > 255)
			ft_error("Error: color rgb not valid!\n", content);
		rgb_int[i] = pixel_ele;
		i++;
	}
	if (i != 3)
		ft_error("Error: invalid rgb formatte!\n", content);
	hex_color = (rgb_int[0] << 16) | (rgb_int[1] << 8) | rgb_int[2];
	if (flag)
		content->floor_color = hex_color;
	else
		content->ceiling_color = hex_color;
	ft_free_2d(rgb);
}
