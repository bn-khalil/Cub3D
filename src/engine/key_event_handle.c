/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:57:01 by kben-tou          #+#    #+#             */
/*   Updated: 2025/07/01 10:57:02 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	key_action(int keycode, t_container *content)
{
	if (keycode == KEY_A)
		content->plr.left = 1;
	else if (keycode == KEY_S)
		content->plr.down = 1;
	else if (keycode == KEY_D)
		content->plr.right = 1;
	else if (keycode == KEY_W)
		content->plr.up = 1;
	else if (keycode == KEY_LEFT)
		content->plr.rotate_left = 1;
	else if (keycode == KEY_RIGHT)
		content->plr.rotate_right = 1;
	else if (keycode == 49)
		content->open_door = 1;
	return (0);
}

int	key_back(int keycode, t_container *content)
{
	if (keycode == KEY_ESC)
		ft_close(content);
	else if (keycode == KEY_A)
		content->plr.left = 0;
	else if (keycode == KEY_S)
		content->plr.down = 0;
	else if (keycode == KEY_D)
		content->plr.right = 0;
	else if (keycode == KEY_W)
		content->plr.up = 0;
	else if (keycode == KEY_LEFT)
		content->plr.rotate_left = 0;
	else if (keycode == KEY_RIGHT)
		content->plr.rotate_right = 0;
	else if (keycode == 49)
		content->open_door = 0;
	return (0);
}
