#include "../../inc/cub3d.h"

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

void map_printer(char **map) {
    int i = 0;
    int j;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            printf("%c", map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
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

void saperate_map_configues(t_container *content)
{
	content->configues = malloc(sizeof(char *) * 7);
	if (!content->configues)
		ft_error("allocation failed!", content);
	int i;

	i = 0;
	while (i < 6 && i < content->map_h)
	{
		content->configues[i] = content->file_content[i];
		i++;
	}
	content->configues[i] = NULL;
	configure_parsing(content);
	// if (content->configues[i][0] == '1' && content->configues[i][content->map_w - 1] == '1')
	// 	ft_error("configuration info not compleated", content);
}

void get_and_init_map(t_container *content)
{
    content->fd_map = open(content->filename, O_RDONLY);
    if (content->fd_map <= 0)
        ft_error("Error opning map file", content);
    content->file_content = ft_split(get_next_line(content), '\n');
    if (!content->file_content || !content->file_content[0])
        ft_error("Error in map maybe empty\n", content);
    get_width_and_height(content);
	saperate_map_configues(content);
    // map_printer(content->configues);
}