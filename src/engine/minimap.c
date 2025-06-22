#include "../../inc/cub3d.h"

void	draw_horizontal_cross(int center_x, int center_y, int color, t_container *content)
{
	int	dx;
	int	t;
	int	half;
	int	thickness;

	half = 2;
	thickness = 1;
	dx = -half;
	while (dx <= half)
	{
		t = -thickness;
		while (t <= thickness)
		{
			print_pxt(center_x + dx, center_y + t, color, content);
			t++;
		}
		dx++;
	}
}

void	draw_vertical_cross(int center_x, int center_y, int color, t_container *content)
{
	int	dy;
	int	t;
	int	half;
	int	thickness;

	half = 2;
	thickness = 1;
	dy = -half;
	while (dy <= half)
	{
		t = -thickness;
		while (t <= thickness)
		{
			print_pxt(center_x + t, center_y + dy, color, content);
			t++;
		}
		dy++;
	}
}

void	draw_diagonal_corners(int center_x, int center_y, int color, t_container *content)
{
	int	i;
	int	sign;
	int	half;

	half = 2;
	i = 0;
	while (i < 2)
	{
		sign = -1;
		if (i != 0)
			sign = 1;
		print_pxt(center_x + sign * half, center_y + sign * half, color, content);
		print_pxt(center_x + sign * half, center_y - sign * half, color, content);
		i++;
	}
}

void	draw_player_shape_minimap(int center_x, int center_y, int color, t_container *content)
{
	draw_horizontal_cross(center_x, center_y, color, content);
	draw_vertical_cross(center_x, center_y, color, content);
	draw_diagonal_corners(center_x, center_y, color, content);
}

void drawLineDDA_minimap(int x0, int y0, int color, t_container *content)
{
    t_line_params *line;
    int            dx_abs;
    int            dy_abs;
    int            i; // Loop counter

    line = content->line_par;
    line->dx = line->end_x - x0;
    line->dy = line->end_y - y0;
    dx_abs = abs(line->dx); // Get absolute values
    dy_abs = abs(line->dy);
    if (dx_abs > dy_abs) {
        line->steps = dx_abs;
    } else {
        line->steps = dy_abs;
    }
    if (line->steps == 0) {
        print_pxt(x0, y0, color, content);
        return;
    }
    line->xInc = (float)line->dx / (float)line->steps; // Explicit float cast for division
    line->yInc = (float)line->dy / (float)line->steps; // Explicit float cast for division
    line->x = (float)x0; // Cast to float as line->x is float
    line->y = (float)y0; // Cast to float as line->y is float
    i = 0; // Initialize loop counter
    while (i <= line->steps) {
        print_pxt((int)roundf(line->x), (int)roundf(line->y), color, content); // Use roundf for float

        line->x += line->xInc;
        line->y += line->yInc;
        i++;
    }
}


void draw_border(t_container *content)
{
    for (int i = 0; i < M_MAP_S; i++) {
        print_pxt(M_M_X + i, M_M_Y, 0xFFFFFF, content); 
        print_pxt(M_M_X + i, M_M_Y + M_MAP_S - 1, 0xFFFFFF, content); 
        print_pxt(M_M_X, M_M_Y + i, 0xFFFFFF, content); 
        print_pxt(M_M_X + M_MAP_S - 1, M_M_Y + i, 0xFFFFFF, content); 
    }
}

void initiale_minimap(t_container *content)
{
    t_minimap *map_inf;

    map_inf = content->minimap;
    map_inf->minimap_radius = M_MAP_S / (2 * M_CELL);
    map_inf->player_map_x = (int)(content->plr.x / PIXEL_SIZE);
    map_inf->player_map_y = (int)(content->plr.y / PIXEL_SIZE);
    map_inf->offset_x = (content->plr.x / PIXEL_SIZE) - map_inf->player_map_x;
    map_inf->offset_y = (content->plr.y / PIXEL_SIZE) - map_inf->player_map_y;
}
void render_minimap(t_container *content)
{
    t_minimap *map_inf;

    map_inf = content->minimap;
    initiale_minimap(content);

    for (int y = 0; y < M_MAP_S; y++) {
        for (int x = 0; x < M_MAP_S; x++) {
            print_pxt(M_M_X+ x, M_M_Y + y, 0x000000, content);
        }
    }

    for (int dy = -map_inf->minimap_radius; dy <= map_inf->minimap_radius; dy++) {
        for (int dx = -map_inf->minimap_radius; dx <= map_inf->minimap_radius; dx++) {
            int map_x = map_inf->player_map_x + dx;
            int map_y = map_inf->player_map_y + dy;

            int minimap_cell_x = M_M_X + ((float)M_MAP_S / 2) + ((dx - map_inf->offset_x) * M_CELL);
            int minimap_cell_y = M_M_Y + ((float)M_MAP_S / 2) + ((dy - map_inf->offset_y) * M_CELL);

            int color = 0x000000;
            if (map_x >= 0 && map_x < content->map_w && 
                map_y >= 0 && map_y < content->map_h) 
            {
                if (content->map[map_y][map_x] == '1') {
                    color = 0xFFFFFF; 
                } else {
                    color = 0x404040; 
                }
            }
            for (int py = 0; py < M_CELL; py++) {
                for (int px = 0; px < M_CELL; px++) {
                    int draw_x = minimap_cell_x + px;
                    int draw_y = minimap_cell_y + py;
                    if (draw_x >= M_M_X && draw_x < M_M_X + M_MAP_S &&
                        draw_y >= M_M_Y && draw_y < M_M_Y + M_MAP_S) {
                        print_pxt(draw_x, draw_y, color, content);
                    }
                }
            }
        }
    }

    int player_minimap_x = M_M_X + (M_MAP_S / 2);
    int player_minimap_y = M_M_Y + (M_MAP_S / 2);

    draw_player_shape_minimap(player_minimap_x, player_minimap_y, 0x00FF00, content);
    float dir_length = 11.0;
    content->line_par->end_x = player_minimap_x + (int)(cos(content->plr.r_angle) * dir_length);
    content->line_par->end_y = player_minimap_y + (int)(sin(content->plr.r_angle) * dir_length);
    drawLineDDA_minimap(player_minimap_x, player_minimap_y, 0xFF0000, content);
    draw_border(content);

}
