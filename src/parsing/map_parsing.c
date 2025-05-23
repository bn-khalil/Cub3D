#include "../../inc/cub3d.h"

int is_map_chars(char c)
{
    if (c == '0' || c == 'N' || c == 'E' || c == 'W' || c == 'S')
        return (1);
    return (0);
}

void spaces_in_map(t_container *content, int x, int y)
{
    if (x < 0 || x > content->map_w || y < 0 || y > content->map_h)
        return ;
    if (y == content->map_h - 1)
    {
        if (is_map_chars(content->map[y][x + 1]) \
        || is_map_chars(content->map[y][x - 1]) \
        || is_map_chars(content->map[y - 1][x]))
            ft_error("Error: invalid map characters!\n", content); 
    }
    else if (is_map_chars(content->map[y][x + 1]) \
    || is_map_chars(content->map[y][x - 1]) \
    || is_map_chars(content->map[y + 1][x]) \
    || is_map_chars(content->map[y - 1][x]))
        ft_error("Error: invalid map characters!\n", content);
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
        if (count > 0)
            ft_error("Error: invalid map there is newline\n", content);
        while (content->map[i][j])
        {
            if (content->map[i][j] == 'N' || content->map[i][j] == 'E' || content->map[i][j] == 'W' || content->map[i][j] == 'S')
            {
                if (!content->player_pos)
                {
                    content->plr.x = j * PIXEL_SIZE;
                    content->plr.y = i * PIXEL_SIZE;
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
            if ((content->map[i][j] == ' ' || content->map[i][j] == '\t'))
                spaces_in_map(content, j, i);
            j++;
        }
        i++;
    }
    if (!content->player_pos)
        ft_error("Error: map doesn't have player\n", content);
}

void parsing_map_content(t_container *content, int start)
{
    int i;
    char **map;

    i = 0;
    while (content->file_content[start + i])
        i++;
    map = malloc(sizeof(char *) * (i + 1));
    if (!map)
        ft_error("Error: allocation failed!\n", content);
    i = 0;
    while (content->file_content[start + i])
    {
        map[i] = content->file_content[start + i];
        i++;
    }
    map[i] = NULL;
    content->map = map;
    get_width_and_height(content);
    check_map_components(content);
}