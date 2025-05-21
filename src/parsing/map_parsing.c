#include "../../inc/cub3d.h"

void newlines_detections(t_container *content)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (content->map[i])
    {
        if (content->map[i][0] == '\0')
            count++;
        i++;
    }
    if (count > 0)
        ft_error("Error: invalid map there is newline\n", content);
    // get_number_newlines
}

void parsing_map_content(t_container *content, int start)
{
    content->map = content->file_content + start;
    newlines_detections(content);
}