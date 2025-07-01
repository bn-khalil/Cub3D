#include "../../inc/cub3d.h"

void	door_check(t_container *content, int i, int j)
{
	if (i < 0 || j < 0 || i >= content->map_w || j >= content->map_h)
		return ;
	if (content->map[i][j - 1] == '1' && content->map[i][j + 1] == '1')
		;
	else if (content->map[i - 1][j] == '1' && content->map[i + 1][j] == '1')
		;
	else
		ft_error("the door doesn't have stands\n", content);
}

void	player_pos_check(t_container *content, int i, int j)
{
	if (content->map[i][j] == 'N'
		|| content->map[i][j] == 'E'
		|| content->map[i][j] == 'W'
		|| content->map[i][j] == 'S')
	{
		if (!content->player_pos)
		{
			content->plr.x = j * PIXEL_SIZE + (PIXEL_SIZE / 2.0f);
			content->plr.y = i * PIXEL_SIZE + (PIXEL_SIZE / 2.0f);
			content->plr.std_direction = content->map[i][j];
			content->player_pos = 1;
		}
		else
			ft_error("Error: map should contain only one plyer position\n",
				content);
	}
}

void	map_sides_check(t_container *content, int i, int j)
{
	if (j == 0 || i == content->map_h - 1
		|| i == 0 || j == ft_strlen(content->map[i]) - 1)
	{
		if (content->map[i][j] != '1'
			&& content->map[i][j] != ' '
			&& content->map[i][j] != '\t')
			ft_error("Error: map should be rounded with walls\n", content);
	}
	if (is_map_chars(content->map[i][j]))
	{
		if (is_map_covered_with_walls(j, i, content))
			ft_error("Error: map should be rounded with walls\n", content);
	}
}

void	map_items_check(t_container *content, int i, int j)
{
	if (content->map[i][j] != '1' && content->map[i][j] != '0'
		&& content->map[i][j] != 'N' && content->map[i][j] != 'W'
		&& content->map[i][j] != 'E' && content->map[i][j] != 'S'
		&& content->map[i][j] != 'D' && content->map[i][j] != ' '
		&& content->map[i][j] != '\t')
		ft_error("Error: invalid map characters!\n", content);
	if (content->map[i][j] == 'D')
		door_check(content, i, j);
}
