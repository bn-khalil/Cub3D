#include "../inc/cub3d.h"

static int	get_number_newlines(char *str)
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
	if (line)
		content->number_of_newlines = get_number_newlines(line);
	return (line);
}

void get_and_init_map(t_container *content)
{
    content->fd_map = open(content->filename, O_RDONLY);
    if (content->fd_map <= 0)
        ft_error("Error opning map file", content);
    content->map = ft_split(get_next_line(content), '\n');
    if (!content->map || !content->map[0])
        ft_error("Error in map maybe empty\n", content);
    printf("file open => %d \n", content->fd_map);
    printf("lines open => %d \n", content->number_of_newlines);
}