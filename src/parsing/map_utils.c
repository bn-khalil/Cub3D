#include "../../inc/cub3d.h"

int	get_number_newlines(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

char	*get_next_line(t_container *content)
{
	char	*buff;
	int		readed;
	char	*line;

	line = NULL;
	buff = malloc(2);
	if (!buff)
		return (NULL);
	readed = 1;
	while (readed > 0)
	{
		readed = read(content->fd_map, buff, 1);
		if (readed == 0)
			break ;
		buff[readed] = '\0';
		line = ft_strjoin(line, buff);
		if (!line)
			break ;
	}
	free(buff);
	content->line = line;
	return (line);
}

void	get_width_and_height(t_container *content)
{
	int	i;
	int	len;
	int	max_width;

	i = 0;
	max_width = 0;
	while (content->map[i])
	{
		len = ft_strlen(content->map[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	content->map_w = max_width;
	content->map_h = i;
}

int	is_map_chars(char c)
{
	if (c == '0' || c == 'N' || c == 'E'
		|| c == 'W' || c == 'S' || c == 'D')
		return (1);
	return (0);
}

char	*ft_complete(t_container *content, char *str)
{
	while (ft_strlen(str) <= content->map_w)
		str = ft_strjoin(str, " ");
	return (str);
}
