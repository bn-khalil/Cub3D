#include "../../inc/cub3d.h"

void player_shape(t_container *content)
{
    int i;

    i = 0;
    print_pxt(content->plr.x + (PLR - 0.5) / 2, content->plr.y + (PLR - 0.5) / 2, 0x00FF00, content);
    print_pxt(content->plr.x - 1 + (PLR - 0.5) / 2, content->plr.y + (PLR - 0.5) / 2, 0x00FF00, content);
    print_pxt(content->plr.x - 2 + (PLR - 0.5) / 2, content->plr.y + (PLR - 0.5) / 2, 0x00FF00, content);
    print_pxt(content->plr.x + 1 + (PLR - 0.5) / 2, content->plr.y + (PLR - 0.5) / 2, 0x00FF00, content);
    print_pxt(content->plr.x + 2 + (PLR - 0.5) / 2, content->plr.y + (PLR - 0.5) / 2, 0x00FF00, content);
    print_pxt(content->plr.x + (PLR - 0.5) / 2, content->plr.y - 1 + (PLR - 0.5) / 2, 0x00FF00, content);
    print_pxt(content->plr.x + (PLR - 0.5) / 2, content->plr.y - 2 + (PLR - 0.5) / 2, 0x00FF00, content);
    print_pxt(content->plr.x + (PLR - 0.5) / 2, content->plr.y + 1 + (PLR - 0.5) / 2, 0x00FF00, content);
    print_pxt(content->plr.x + (PLR - 0.5) / 2, content->plr.y + 2 + (PLR - 0.5) / 2, 0x00FF00, content);
}

void drawing_plr(t_container *content)
{
    int i = 0;

    while (i < PLR)
    {
        if (i < PLR / 3 || i > PLR / 1.5 )
        {
            print_pxt(content->plr.x + i,content->plr.y , 0x00FF00, content);
            print_pxt(content->plr.x + i,content->plr.y + 2 , 0x00FF00, content);
        }
        i++;
    }
    i = 0;
    while (i < PLR)
    {
        if (i < PLR / 3 || i > PLR / 1.5 )
        {
            print_pxt(content->plr.x, content->plr.y + i, 0x00FF00, content);
            print_pxt(content->plr.x + 2, content->plr.y + i, 0x00FF00, content);
        }
        i++;
    }
    i = 0;
    while (i < PLR)
    {
        if (i < PLR / 3 || i > PLR / 1.5 )
        {
            print_pxt(content->plr.x + i, content->plr.y + PLR - 1, 0x00FF00, content);
            print_pxt(content->plr.x + i, content->plr.y + PLR - 3, 0x00FF00, content);
        }
        i++;
    }
    i = 0;
    while (i < PLR)
    {
        if (i < PLR / 3 || i > PLR / 1.5)
        {
            print_pxt(content->plr.x + PLR - 1, content->plr.y + i, 0x00FF00, content);
            print_pxt(content->plr.x + PLR - 3, content->plr.y + i, 0x00FF00, content);
        }
        i++;
    }
    player_shape(content);
}
