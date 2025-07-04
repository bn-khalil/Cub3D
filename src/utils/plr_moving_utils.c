/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plr_moving_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:55:02 by kben-tou          #+#    #+#             */
/*   Updated: 2025/07/03 14:55:03 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

float	fix_angle(float angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

int	is_wall(float x, float y, t_container *content)
{
	int	i;
	int	j;

	i = (int)(x / PIXEL_SIZE);
	j = (int)(y / PIXEL_SIZE);
	if (!content || !content->map)
		return (1);
	if (i < 0 || j < 0 || j >= content->map_h || i >= content->map_w)
		return (1);
	if (content->map[j][i] == '1' || content->map[j][i] == 'D')
		return (1);
	return (0);
}

int	ft_is_collision(float x, float y, t_container *content)
{
	float	offsets[4][2];
	int		i;

	offsets[0][0] = -PLR;
	offsets[0][1] = -PLR;
	offsets[1][0] = PLR;
	offsets[1][1] = -PLR;
	offsets[2][0] = -PLR;
	offsets[2][1] = PLR;
	offsets[3][0] = PLR;
	offsets[3][1] = PLR;
	i = 0;
	while (i < 4)
	{
		if (is_wall(x + offsets[i][0], y + offsets[i][1], content))
			return (1);
		i++;
	}
	return (0);
}

void	updated_x_y(t_container *content, float new_x, float new_y)
{
	content->plr.x = new_x;
	content->plr.y = new_y;
}
