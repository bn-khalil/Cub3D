/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_dete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:53:12 by kben-tou          #+#    #+#             */
/*   Updated: 2025/07/01 10:53:32 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	mouse_detection(int x, int y, void *data)
{
	t_container	*content;
	float		speed;
	float		d_x;

	content = (t_container *)data;
	speed = 0.002;
	if (x < 0 || x > MAP_W)
	{
		content->mouse_press = 0;
		content->old_mouse_x = 0;
	}
	else if (content->mouse_press && content->old_mouse_x >= 0 && \
		x >= 0 && x < MAP_W && y >= 0 && y < MAP_H)
	{
		d_x = content->old_mouse_x - x;
		content->plr.r_angle -= d_x * speed;
		content->plr.r_angle = fix_angle(content->plr.r_angle);
		content->old_mouse_x = x;
	}
	return (0);
}

int	mouse_press(int button, int x, int y, void *data)
{
	t_container	*content;

	content = (t_container *)data;
	if (button == 1 && x >= 0 && x < MAP_W && y >= 0 && y < MAP_H)
	{
		content->mouse_press = 1;
		content->old_mouse_x = x;
	}
	return (0);
}

int	mouse_release(int button, int x, int y, void *data)
{
	t_container	*content;

	content = (t_container *)data;
	if (button == 1 && x >= 0 && x < MAP_W && y >= 0 && y < MAP_H)
	{
		content->mouse_press = 0;
		content->old_mouse_x = 0;
	}
	return (0);
}
