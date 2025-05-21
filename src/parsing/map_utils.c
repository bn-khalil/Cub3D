#include "../../inc/cub3d.h"

int	get_number_newlines(char *str)
{
	int		i;
	int		count;

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

void get_width_and_height(t_container *content)
{
    int i;
    content->map_w = ft_strlen(content->file_content[0]);

    i = 0;
    while (content->file_content[i])
        i++;
    content->map_h = i;
}