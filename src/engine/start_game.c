#include "../../inc/cub3d.h"
#include <float.h>

void drawLineDDA(int x0, int y0, int x1, int y1, int color, t_container *content) 
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = x0;
    float y = y0;
    int i = 0;

    while (i <= steps) {
        print_pxt((int)round(x) * MAP_RATIO, (int)round(y) * MAP_RATIO, color, content);
        x += xInc;
        y += yInc;
        i++;
    }
}

void render_minimap(t_container *content)
{
    int center_x = MINIMAP_WIDTH / 2;
    int center_y = MINIMAP_HEIGHT / 2;
    
    int player_map_x = content->plr.x / PIXEL_SIZE;
    int player_map_y = content->plr.y / PIXEL_SIZE;
    
    int start_x = player_map_x - (MINIMAP_WIDTH / (2 * MINIMAP_CELL_SIZE));
    int start_y = player_map_y - (MINIMAP_HEIGHT / (2 * MINIMAP_CELL_SIZE));
    int end_x = start_x + (MINIMAP_WIDTH / MINIMAP_CELL_SIZE);
    int end_y = start_y + (MINIMAP_HEIGHT / MINIMAP_CELL_SIZE);
    
    for (int y = 0; y < MINIMAP_HEIGHT; y++) {
        for (int x = 0; x < MINIMAP_WIDTH; x++) {
            if (x < MINIMAP_BORDER || x >= MINIMAP_WIDTH - MINIMAP_BORDER ||
                y < MINIMAP_BORDER || y >= MINIMAP_HEIGHT - MINIMAP_BORDER) {
                print_pxt(x, y, 0x000000, content); 
            } else {
                print_pxt(x, y, 0x333333, content); // Dark background
            }
        }
    }
    
    for (int map_y = start_y; map_y < end_y; map_y++) {
        for (int map_x = start_x; map_x < end_x; map_x++) {
            if (map_x >= 0 && map_x < content->map_w &&
                map_y >= 0 && map_y < content->map_h) {
                
                int screen_x = center_x + (map_x - player_map_x) * MINIMAP_CELL_SIZE;
                int screen_y = center_y + (map_y - player_map_y) * MINIMAP_CELL_SIZE;
                
                for (int dy = 0; dy < MINIMAP_CELL_SIZE; dy++) {
                    for (int dx = 0; dx < MINIMAP_CELL_SIZE; dx++) {
                        int px = screen_x + dx - MINIMAP_CELL_SIZE/2;
                        int py = screen_y + dy - MINIMAP_CELL_SIZE/2;
                        
                        if (px >= MINIMAP_BORDER && px < MINIMAP_WIDTH - MINIMAP_BORDER &&
                            py >= MINIMAP_BORDER && py < MINIMAP_HEIGHT - MINIMAP_BORDER) {
                            if (content->map[map_y][map_x] == '1') {
                                print_pxt(px, py, 0xFFFFFF, content); // White walls
                            } else if (content->map[map_y][map_x] == '0') {
                                print_pxt(px, py, 0x555555, content); // Gray floor
                            }
                        }
                    }
                }
            }
        }
    }
    
    /* int player_size = 3; */
    /* for (int dy = -player_size; dy <= player_size; dy++) { */
    /*     for (int dx = -player_size; dx <= player_size; dx++) { */
    /*         int px = center_x + dx; */
    /*         int py = center_y + dy; */
    /*          */
    /*         if ((dx == 0 || dy == 0) && (abs(dx) <= player_size/2 && abs(dy) <= player_size/2)) { */
    /*             if (px >= 0 && px < MINIMAP_WIDTH && py >= 0 && py < MINIMAP_HEIGHT) { */
    /*                 print_pxt(px, py, 0xFF0000, content); // Red player */
    /*             } */
    /*         } */
    /*     } */
    /* } */
    
    /* // Optional: Draw player direction line */
    /* float line_length = MINIMAP_CELL_SIZE * 1.5; */
    /* int end_x_dir = center_x + (int)(cos(content->plr.r_angle) * line_length); */
    /* int end_y_dir = center_y + (int)(sin(content->plr.r_angle) * line_length); */
    /*  */
    /* drawLineDDA(center_x, center_y, end_x_dir, end_y_dir, 0xFF0000, content); */
}
float fix_angle(float angle)
{
    angle = fmod(angle, 2 * PI);
    if (angle < 0)
        angle += 2 * PI;
    return angle;
}


void init_player(t_container *content) {
    content->plr.up = 0;
    content->plr.down = 0;
    content->plr.left = 0;
    content->plr.right = 0;
    content->plr.speed = 6.5;
    content->plr.rotate_left = 0;
    content->plr.rotate_right = 0;
    content->num_rays = (content->map_w * PIXEL_SIZE) / WALL_COL_WIDH;
    content->rays = malloc(sizeof(t_ray) * content->num_rays);
    ft_memset(content->rays, 0, sizeof(t_ray) * content->num_rays);
    
    if (content->plr.std_direction == 'E')
        content->plr.r_angle = 0;
    if (content->plr.std_direction == 'W')
        content->plr.r_angle = PI;
    if (content->plr.std_direction == 'N')
        content->plr.r_angle = PI / 2;
    if (content->plr.std_direction == 'S')
        content->plr.r_angle = 3 * PI / 2;
    
    content->plr.r_speed = 3 * (PI / 180);  
}

void mlx_res_init(t_container *content) {
    init_player(content);
    content->src.mlx = mlx_init();
    content->src.win = mlx_new_window(content->src.mlx, content->map_w * PIXEL_SIZE, 
                                     content->map_h * PIXEL_SIZE, "Cub3D");
    content->src.img = mlx_new_image(content->src.mlx, content->map_w * PIXEL_SIZE, 
                                    content->map_h * PIXEL_SIZE);
    content->src.buffer_pos = mlx_get_data_addr(content->src.img, 
                                              &content->src.pixel_bits_number, 
                                              &content->src.len_with_pixels, 
                                              &content->src.endian);
}

int ft_close(t_container *content) {
    (void)content;
    exit(0);
    return 0;
}

int key_action(int keycode, t_container *content) {
    if (keycode == KEY_A)
        content->plr.left = 1;
    else if (keycode == KEY_S)
        content->plr.down = 1;
    else if (keycode == KEY_D)
        content->plr.right = 1;
    else if (keycode == KEY_W)
        content->plr.up = 1;
    else if (keycode == KEY_LEFT)
        content->plr.rotate_left = 1;
    else if (keycode == KEY_RIGHT)
        content->plr.rotate_right = 1;
    return 0;
}

int key_back(int keycode, t_container *content) {
    if (keycode == KEY_ESC)
        ft_close(content);
    else if (keycode == KEY_A)
        content->plr.left = 0;
    else if (keycode == KEY_S)
        content->plr.down = 0;
    else if (keycode == KEY_D)
        content->plr.right = 0;
    else if (keycode == KEY_W)
        content->plr.up = 0;
    else if (keycode == KEY_LEFT)
        content->plr.rotate_left = 0;
    else if (keycode == KEY_RIGHT)
        content->plr.rotate_right = 0;
    return 0;
}

int is_wall(float x, float y, t_container *content) {
    int i = (int)(x / PIXEL_SIZE);
    int j = (int)(y / PIXEL_SIZE);

    if (i < 0 || j < 0 || i >= content->map_w || j >= content->map_h)
        return 1;

    if (!content->map || !content->map[j])
        return 1;

    if (content->map[j][i] == '1')
        return 1;

    return 0;
}

int ft_is_collision(float x, float y, t_container *content) {
    if (is_wall(x, y, content) || 
        is_wall(x + (float)PLR, y, content) ||
        is_wall(x, y + (float)PLR, content) ||
        is_wall(x + (float)PLR, y + (float)PLR, content)) {
        return 1;
    }
    return 0;
}

void let_player_move(t_container *content) {
    content->plr.r_angle = fix_angle(content->plr.r_angle);

    if (content->plr.rotate_left)
        content->plr.r_angle -= content->plr.r_speed;
    if (content->plr.rotate_right)
        content->plr.r_angle += content->plr.r_speed;

    content->plr.r_angle = fix_angle(content->plr.r_angle);

    float cos_an = cos(content->plr.r_angle);
    float sin_an = sin(content->plr.r_angle);

    if (fabs(cos_an) < 0.0001) 
        cos_an = 0;
    if (fabs(sin_an) < 0.0001) 
        sin_an = 0;

    float new_x = content->plr.x;
    float new_y = content->plr.y;

    if (content->plr.up) {
        new_x = content->plr.x + cos_an * content->plr.speed;
        new_y = content->plr.y + sin_an * content->plr.speed;
        if (!ft_is_collision(new_x, new_y, content)) {
            content->plr.x = new_x;
            content->plr.y = new_y;
        }
    }
    if (content->plr.down) {
        new_x = content->plr.x - cos_an * content->plr.speed;
        new_y = content->plr.y - sin_an * content->plr.speed;
        if (!ft_is_collision(new_x, new_y, content)) {
            content->plr.x = new_x;
            content->plr.y = new_y;
        }
    }
    if (content->plr.left) {
        new_x = content->plr.x + sin_an * content->plr.speed;
        new_y = content->plr.y - cos_an * content->plr.speed;
        if (!ft_is_collision(new_x, new_y, content)) {
            content->plr.x = new_x;
            content->plr.y = new_y;
        }
    }
    if (content->plr.right) {
        new_x = content->plr.x - sin_an * content->plr.speed;
        new_y = content->plr.y + cos_an * content->plr.speed;
        if (!ft_is_collision(new_x, new_y, content)) {
            content->plr.x = new_x;
            content->plr.y = new_y;
        }
    }
}

float get_vector_dis(t_container *content, float nex_x, float nex_y)
{
    return sqrt((nex_x - content->plr.x) * (nex_x - content->plr.x) + 
               (nex_y - content->plr.y) * (nex_y - content->plr.y));
}

void get_the_smallest(t_ray *ray, float ray_angle, float player_angle)
{
    if (ray->horiz_distance < ray->ver_distance) {
        ray->wall_hit_x = ray->horiz_hit_x;
        ray->wall_hit_y = ray->horiz_hit_y;
        ray->distance = ray->horiz_distance;
        ray->was_vertical = 0;
    }
    else {
        ray->wall_hit_x = ray->ver_hit_x;
        ray->wall_hit_y = ray->ver_hit_y;
        ray->distance = ray->ver_distance;
        ray->was_vertical = 1;
    }
    ray->distance *= cos(ray_angle - player_angle);
}

void ray_info(t_container *content)
{
    int i = -1;
    float ray_angle = fix_angle(content->plr.r_angle - (FOV / 2));
    
    while (++i < content->num_rays) 
    {
        content->rays[i].is_hit_horizontal = 0;
        content->rays[i].is_hit_vertical = 0;
        
        content->rays[i].is_ray_down = ray_angle > 0 && ray_angle < PI;
        content->rays[i].is_ray_up = !content->rays[i].is_ray_down;
        content->rays[i].is_ray_right = ray_angle < (PI / 2) || ray_angle > 1.5 * PI;
        content->rays[i].is_ray_left = !content->rays[i].is_ray_right;

        float y_intercept = floor(content->plr.y / PIXEL_SIZE) * PIXEL_SIZE;
        if (content->rays[i].is_ray_down)
            y_intercept += PIXEL_SIZE;
            
        float x_intercept = content->plr.x + (y_intercept - content->plr.y) / tan(ray_angle);
        
        float y_step = PIXEL_SIZE;
        if (content->rays[i].is_ray_up)
            y_step *= -1;
            
        float x_step = PIXEL_SIZE / tan(ray_angle);
        if ((content->rays[i].is_ray_left && x_step > 0) || 
            (content->rays[i].is_ray_right && x_step < 0))
            x_step *= -1;
            
        float next_h_x = x_intercept;
        float next_h_y = y_intercept;
        
        while (next_h_x >= 0 && next_h_x <= content->map_w * PIXEL_SIZE &&
               next_h_y >= 0 && next_h_y <= content->map_h * PIXEL_SIZE)
        {
            if (content->rays[i].is_ray_up) {
                if (is_wall(next_h_x, next_h_y - 1, content)) {
                    content->rays[i].is_hit_horizontal = 1;
                    content->rays[i].horiz_hit_x = next_h_x;
                    content->rays[i].horiz_hit_y = next_h_y;
                    break;
                }
            }
            
            else if (is_wall(next_h_x, next_h_y, content)) {
                content->rays[i].is_hit_horizontal = 1;
                content->rays[i].horiz_hit_x = next_h_x;
                content->rays[i].horiz_hit_y = next_h_y;
                break;
            }
            
            next_h_x += x_step;
            next_h_y += y_step;
        }

float x_v_intercept = floor(content->plr.x / PIXEL_SIZE) * PIXEL_SIZE;
if (content->rays[i].is_ray_right)
    x_v_intercept += PIXEL_SIZE;

float y_v_intercept = content->plr.y + (x_v_intercept - content->plr.x) * tan(ray_angle);

float x_v_step = PIXEL_SIZE;
if (content->rays[i].is_ray_left)
    x_v_step *= -1;

float y_v_step = PIXEL_SIZE * tan(ray_angle);
if ((content->rays[i].is_ray_up && y_v_step > 0) || 
    (content->rays[i].is_ray_down && y_v_step < 0))
    y_v_step *= -1;

float next_v_x = x_v_intercept;
float next_v_y = y_v_intercept;

while (next_v_x >= 0 && next_v_x <= content->map_w * PIXEL_SIZE &&
       next_v_y >= 0 && next_v_y <= content->map_h * PIXEL_SIZE)
{
    float check_x = next_v_x;
    float check_y = next_v_y;
    
    if (content->rays[i].is_ray_left) 
        check_x -= 1.0;
    
    if (is_wall(check_x, check_y, content)) {
        content->rays[i].is_hit_vertical = 1;
        content->rays[i].ver_hit_x = next_v_x;
        content->rays[i].ver_hit_y = next_v_y;
        break;
    }
    
    next_v_x += x_v_step;
    next_v_y += y_v_step;
}

        if (content->rays[i].is_hit_horizontal) {
            content->rays[i].horiz_distance = get_vector_dis(content, 
                content->rays[i].horiz_hit_x, content->rays[i].horiz_hit_y);
        } else {
            content->rays[i].horiz_distance = FLT_MAX;
        }

        if (content->rays[i].is_hit_vertical) {
            content->rays[i].ver_distance = get_vector_dis(content, 
                content->rays[i].ver_hit_x, content->rays[i].ver_hit_y);
        } else {
            content->rays[i].ver_distance = FLT_MAX;
        }

        get_the_smallest(&content->rays[i], ray_angle, content->plr.r_angle);
        ray_angle = fix_angle(ray_angle + (FOV / content->num_rays));
    }
}

void convert_2d_to_3d(t_container *content)
{
    int i;
    t_ray ray;
    float distance_projection;
    float wall_hight;
    int color;
    i = -1;
    int y;
    distance_projection = ((content->map_w * PIXEL_SIZE) / 2.0 ) / tan(FOV / 2.0);
    while (++i < content->num_rays)
    {
        ray = content->rays[i];
        wall_hight = (PIXEL_SIZE / ray.distance) * distance_projection;
        int wall_strip_high = (int)wall_hight;
        int wall_top_pixel = ((content->map_h * PIXEL_SIZE) / 2) - (wall_strip_high / 2);
        if (wall_top_pixel < 0)
            wall_top_pixel = 0;
        int botm_pixel = ((content->map_h * PIXEL_SIZE) / 2) + (wall_strip_high / 2);
        if (botm_pixel > (content->map_h * PIXEL_SIZE))
            botm_pixel = content->map_h * PIXEL_SIZE;
        y = wall_top_pixel;
        if (ray.was_vertical) {
            color = 0xA0A0A0; 
        } else {
            color = 0xFFFFFF; 
}
        for (int y = wall_top_pixel; y < botm_pixel; y++) {
            print_pxt(i * (content->map_w * PIXEL_SIZE / content->num_rays), y, color, content);
        }

    }
}

void cast_all_rays(t_container *content) {
    int i = -1;
    while (++i < content->num_rays)
    {
        drawLineDDA(content->plr.x, content->plr.y, 
                   content->rays[i].wall_hit_x, content->rays[i].wall_hit_y, 
                   0x00FF00, content);
    }
}

int draw_game(t_container *content) {
    let_player_move(content);
    ray_info(content);
    clear_map_after_player(content);
    convert_2d_to_3d(content);
    render_minimap(content);
    /* drawing_plr(content); */
    /* cast_all_rays(content); */
    mlx_put_image_to_window(content->src.mlx, content->src.win, content->src.img, 0, 0);
    return (0);
}

void start_the_play(t_container *content) {
    mlx_res_init(content);
    /* draw_map(content); */
    mlx_put_image_to_window(content->src.mlx, content->src.win, content->src.img, 0, 0);
    mlx_hook(content->src.win, 17, 0, ft_close, content);
    mlx_hook(content->src.win, 2, 1L << 0, key_action, content);
    mlx_hook(content->src.win, 3, 1L << 1, key_back, content);
    mlx_loop_hook(content->src.mlx, draw_game, content);
    mlx_loop(content->src.mlx);
}
