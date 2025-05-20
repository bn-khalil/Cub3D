#include "../../inc/cub3d.h"

void configure_parsing(t_container *content)
{
    int i;

    i = 0;
    while (content->configues[i])
    {
        if (ft_strncmp("NO ", content->configues[i], 3) == 0)
            configue_direction_parsing(content, ft_substr(content->configues[i], 0, 3), ft_substr(content->configues[i], 3, ft_strlen(content->configues[i])));
        else if (ft_strncmp("SO ", content->configues[i], 3) == 0)
            configue_direction_parsing(content, ft_substr(content->configues[i], 0, 3), ft_substr(content->configues[i], 3, ft_strlen(content->configues[i])));
        else if (ft_strncmp("WE ", content->configues[i], 3) == 0)
            configue_direction_parsing(content, ft_substr(content->configues[i], 0, 3), ft_substr(content->configues[i], 3, ft_strlen(content->configues[i])));
        else if (ft_strncmp("EA ", content->configues[i], 3) == 0)
            configue_direction_parsing(content, ft_substr(content->configues[i], 0, 3), ft_substr(content->configues[i], 3, ft_strlen(content->configues[i])));
        else if (ft_strncmp("F ", content->configues[i], 2) == 0)
           configue_rgb_parsing(content, content->configues[i]);
        else if (ft_strncmp("C ", content->configues[i], 2) == 0)
            configue_rgb_parsing(content, content->configues[i]);
        else
            ft_error("Error: missing or invalid identifier\n", content);
        i++;
    }
	print_list(content->confs);
}
