#include "../../inc/cub3d.h"

// void check_map_chars(char *str, t_container *content)
// {
//     int i;

//     i = 0;

    
// }
int is_map_chars(char c)
{
    if (c == '1' || c == '0' || c == 'N' || c == 'E' || c == 'W' || c == 'S')
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
            if (content->map[i][j] != '1' && content->map[i][j] != '0' && content->map[i][j] != 'N' && content->map[i][j] != 'W' && content->map[i][j] != 'E' && content->map[i][j] != 'S' && content->map[i][j] != ' ' && content->map[i][j] != '\t')
                ft_error("Error: invalid map characters!\n", content);
            if ((content->map[i][j] == ' ' || content->map[i][j] == '\t') && (is_map_chars(content->map[i][j + 1]) && is_map_chars(content->map[i][j - 1]) && is_map_chars(content->map[i + 1][j]) && is_map_chars(content->map[i - 1][j])))
                ft_error("Error: invalid map characters!\n", content);
            j++;
        }
        i++;
    }
    if (count > 0)
        ft_error("Error: invalid map there is newline\n", content);
}

void parsing_map_content(t_container *content, int start)
{
    content->map = content->file_content + start;
    check_map_components(content);
}