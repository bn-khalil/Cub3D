#include "../../inc/cub3d.h"

void draw_player_shape_minimap(int center_x, int center_y, int color, t_container *content)
{
    int half = 2; 
    int thickness = 1;

    for (int dx = -half; dx <= half; dx++) {
        for (int t = -thickness; t <= thickness; t++) {
            print_pxt(center_x + dx, center_y + t, color, content);
        }
    }
    for (int dy = -half; dy <= half; dy++) {
        for (int t = -thickness; t <= thickness; t++) {
            print_pxt(center_x + t, center_y + dy, color, content);
        }
    }
    for (int i = 0; i < 2; i++) {
        int sign = i ? 1 : -1;
        print_pxt(center_x + sign*half, center_y + sign*half, color, content);
        print_pxt(center_x + sign*half, center_y - sign*half, color, content);
    }
}

void drawLineDDA_minimap(int x0, int y0, int x1, int y1, int color, t_container *content) 
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    
    if (steps == 0) {
        print_pxt(x0, y0, color, content);
        return;
    }
    
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = x0;
    float y = y0;
    
    for (int i = 0; i <= steps; i++) {
        print_pxt((int)round(x), (int)round(y), color, content);
        x += xInc;
        y += yInc;
    }
}

void render_minimap(t_container *content)
{
    int minimap_size = 200; 
    int minimap_x = 10;
    int minimap_y = 10;
    int cell_size = 8;      
    int minimap_radius = minimap_size / (2 * cell_size);

    int player_map_x = (int)(content->plr.x / PIXEL_SIZE);
    int player_map_y = (int)(content->plr.y / PIXEL_SIZE);

    float player_cell_offset_x = (content->plr.x / PIXEL_SIZE) - player_map_x;
    float player_cell_offset_y = (content->plr.y / PIXEL_SIZE) - player_map_y;

    for (int y = 0; y < minimap_size; y++) {
        for (int x = 0; x < minimap_size; x++) {
            print_pxt(minimap_x + x, minimap_y + y, 0x000000, content);
        }
    }

    for (int dy = -minimap_radius; dy <= minimap_radius; dy++) {
        for (int dx = -minimap_radius; dx <= minimap_radius; dx++) {
            int map_x = player_map_x + dx;
            int map_y = player_map_y + dy;

            int minimap_cell_x = minimap_x + (minimap_size / 2) + ((dx - player_cell_offset_x) * cell_size);
            int minimap_cell_y = minimap_y + (minimap_size / 2) + ((dy - player_cell_offset_y) * cell_size);

            int color = 0x000000;
            if (map_x >= 0 && map_x < content->map_w && 
                map_y >= 0 && map_y < content->map_h) 
            {
                if (content->map[map_y][map_x] && content->map[map_y][map_x] == '1') {
                    color = 0xFFFFFF; 
                } else {
                    color = 0x404040; 
                }
            }
            for (int py = 0; py < cell_size; py++) {
                for (int px = 0; px < cell_size; px++) {
                    int draw_x = minimap_cell_x + px;
                    int draw_y = minimap_cell_y + py;
                    if (draw_x >= minimap_x && draw_x < minimap_x + minimap_size &&
                        draw_y >= minimap_y && draw_y < minimap_y + minimap_size) {
                        print_pxt(draw_x, draw_y, color, content);
                    }
                }
            }
        }
    }

    int player_minimap_x = minimap_x + (minimap_size / 2);
    int player_minimap_y = minimap_y + (minimap_size / 2);

    draw_player_shape_minimap(player_minimap_x, player_minimap_y, 0x00FF00, content);
    float dir_length = 11.0;
    int end_x = player_minimap_x + (int)(cos(content->plr.r_angle) * dir_length);
    int end_y = player_minimap_y + (int)(sin(content->plr.r_angle) * dir_length);
    drawLineDDA_minimap(player_minimap_x, player_minimap_y, end_x, end_y, 0xFF0000, content);
    for (int i = 0; i < minimap_size; i++) {
        print_pxt(minimap_x + i, minimap_y, 0xFFFFFF, content); // Top
        print_pxt(minimap_x + i, minimap_y + minimap_size - 1, 0xFFFFFF, content); // Bottom
        print_pxt(minimap_x, minimap_y + i, 0xFFFFFF, content); // Left
        print_pxt(minimap_x + minimap_size - 1, minimap_y + i, 0xFFFFFF, content); // Right
    }
}
