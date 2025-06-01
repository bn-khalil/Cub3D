#include "../../inc/cub3d.h"

int is_map_chars(char c) {
  if (c == '0' || c == 'N' || c == 'E' || c == 'W' || c == 'S')
    return (1);
  return (0);
}

int is_map_covered_with_walls(int x, int y, t_container *content)
{
    if (x < 0 || x >= ft_strlen(content->map[y]) \
    || y < 0 || y >= content->map_h)
        return (0);
    if (x - 1 < 0 || y - 1 < 0)
        return (0);
    if (content->map[y - 1][x] == ' ' \
    || content->map[y - 1][x] == '\t' \
    || content->map[y + 1][x] == ' ' \
    || content->map[y + 1][x] == '\t')
        return (1);
    if (content->map[y][x - 1] == ' ' \
    || content->map[y][x - 1] == '\t' \
    || content->map[y][x + 1] == ' ' \
    || content->map[y][x + 1] == '\t')
        return (1);
    if (x >= ft_strlen(content->map[y - 1]) \
    || x >= ft_strlen(content->map[y + 1]))
        return (1);
    return (0);
}


void check_map_components(t_container *content)
{
    int i;
    int count;
    int j;

    i = 0;
    count = 0;
    while (content->map[i])
    {
        j = 0;
        if (content->map[i][0] == '\0')
            count++;
        while (content->map[i][j])
        {
            if (content->map[i][j] == 'N' \
            || content->map[i][j] == 'E' \
            || content->map[i][j] == 'W' \
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
                    ft_error("Error: map should contain only one plyer position\n", content);
            }
            if (j == 0 || i == content->map_h - 1 || i == 0 || j == ft_strlen(content->map[i]) - 1)
            {
                if (content->map[i][j] != '1' && content->map[i][j] != ' ' && content->map[i][j] != '\t')
                    ft_error("Error: map should be rounded with walls\n", content);
            }
            if (content->map[i][j] != '1' && content->map[i][j] != '0' \
            && content->map[i][j] != 'N' && content->map[i][j] != 'W' \
            && content->map[i][j] != 'E' && content->map[i][j] != 'S' \
            && content->map[i][j] != ' ' && content->map[i][j] != '\t')
                ft_error("Error: invalid map characters!\n", content);
            if (is_map_chars(content->map[i][j]))
            {
                if (is_map_covered_with_walls(j , i, content))
                    ft_error("Error: map should be rounded with walls\n", content);
            }
            j++;
        }
        i++;
    }
    if (!content->player_pos)
        ft_error("Error: map doesn't have player\n", content);
}

int check_newlines(t_container *content, int start, int i)
{
    while (ft_strcmp(content->file_content[start + i], "\n") == 0)
        i++;
    if (content->file_content[start + i] != NULL)
            ft_error("Error: invalid map there is newline\n", content);
    return (start + i);
}

void parsing_map_content(t_container *content, int start)
{
    int i;
    int j;
    int stop;

    i = 0;
    while (content->file_content[start + i])
        i++;
    content->map = malloc(sizeof(char *) * (i + 1));
    if (!content->map)
        ft_error("Error: allocation failed!\n", content);
    i = 0;
    stop = 0;
    while (content->file_content[start + i])
    {
        if (is_paces(content->file_content[start + i]))
        {
            j = start + i;
            while (content->file_content[j] && is_paces(content->file_content[j]))
                j++;
            if (content->file_content[j] == NULL)
                stop++;
        }
        if (stop)
            break ;
        content->map[i] = content->file_content[start + i];
        i++;
    }
    content->map[i] = NULL;
    get_width_and_height(content);
    map_printer(content->map);
    check_map_components(content);
}
