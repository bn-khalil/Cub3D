#include "../../inc/cub3d.h"
#include <float.h>

#define FOV (60.0 * (PI / 180.0))  // Field of View in radians (60 degrees)

float fix_angle(float angle)
{
    angle = fmod(angle, 2 * PI);
    if (angle < 0)
        angle += 2 * PI;
    return angle;
}

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
        print_pxt((int)round(x), (int)round(y), color, content);
        x += xInc;
        y += yInc;
        i++;
    }
}

void init_player(t_container *content) {
    content->plr.up = 0;
    content->plr.down = 0;
    content->plr.left = 0;
    content->plr.right = 0;
    content->plr.speed = 1.5;
    content->plr.rotate_left = 0;
    content->plr.rotate_right = 0;
    content->num_rays = content->map_w / WALL_COL_WIDH;
    content->rays = malloc(sizeof(t_ray) * content->num_rays);
    ft_memset(content->rays, 0, sizeof(t_ray) * content->num_rays);
    
    // Corrected angle initialization
    if (content->plr.std_direction == 'E')
        content->plr.r_angle = 0;
    if (content->plr.std_direction == 'W')
        content->plr.r_angle = PI;
    if (content->plr.std_direction == 'N')
        content->plr.r_angle = PI / 2;
    if (content->plr.std_direction == 'S')
        content->plr.r_angle = 3 * PI / 2;
    
    content->plr.r_speed = 1 * (PI / 180);  // 1 degree per frame
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

    if (fabs(cos_an) < 0.0001) cos_an = 0;
    if (fabs(sin_an) < 0.0001) sin_an = 0;

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
    }
    else {
        ray->wall_hit_x = ray->ver_hit_x;
        ray->wall_hit_y = ray->ver_hit_y;
        ray->distance = ray->ver_distance;
    }
    // Fish-eye correction
    ray->distance *= cos(ray_angle - player_angle);
}

void ray_info(t_container *content)
{
    int i = -1;
    float ray_angle = fix_angle(content->plr.r_angle - (FOV / 2));
    
    while (++i < content->num_rays) 
    {
        int is_hit_horizontal = 0;
        int is_hit_vertical = 0;
        
        content->rays[i].is_ray_down = ray_angle > 0 && ray_angle < PI;
        content->rays[i].is_ray_up = !content->rays[i].is_ray_down;
        content->rays[i].is_ray_right = ray_angle < (PI / 2) || ray_angle > 1.5 * PI;
        content->rays[i].is_ray_left = !content->rays[i].is_ray_right;

        /* Horizontal intersection */
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
        
        if (content->rays[i].is_ray_up)
            next_h_y -= 1;  // Avoid floating point precision issues
            
        while (next_h_x >= 0 && next_h_x <= content->map_w * PIXEL_SIZE &&
               next_h_y >= 0 && next_h_y <= content->map_h * PIXEL_SIZE)
        {
            if (is_wall(next_h_x, next_h_y, content)) {
                is_hit_horizontal = 1;
                content->rays[i].horiz_hit_x = next_h_x;
                content->rays[i].horiz_hit_y = next_h_y;
                break;
            }
            next_h_x += x_step;
            next_h_y += y_step;
        }

        /* Vertical intersection */
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
        
        if (content->rays[i].is_ray_left)
            next_v_x -= 1;  // Avoid floating point precision issues
            
        while (next_v_x >= 0 && next_v_x <= content->map_w * PIXEL_SIZE &&
               next_v_y >= 0 && next_v_y <= content->map_h * PIXEL_SIZE)
        {
            if (is_wall(next_v_x, next_v_y, content)) {
                is_hit_vertical = 1;
                content->rays[i].ver_hit_x = next_v_x;
                content->rays[i].ver_hit_y = next_v_y;
                break;
            }
            next_v_x += x_v_step;
            next_v_y += y_v_step;
        }

        // Calculate distances
        content->rays[i].horiz_distance = is_hit_horizontal ? 
            get_vector_dis(content, content->rays[i].horiz_hit_x, content->rays[i].horiz_hit_y) : FLT_MAX;
            
        content->rays[i].ver_distance = is_hit_vertical ? 
            get_vector_dis(content, content->rays[i].ver_hit_x, content->rays[i].ver_hit_y) : FLT_MAX;

        // Determine closest hit
        get_the_smallest(&content->rays[i], ray_angle, content->plr.r_angle);
        
        // Draw debug ray
        drawLineDDA(content->plr.x, content->plr.y, 
                   content->rays[i].wall_hit_x, content->rays[i].wall_hit_y, 
                   0x00FF00, content);
        
        // Increment angle for next ray
        ray_angle = fix_angle(ray_angle + (FOV / content->num_rays));
    }
}

void cast_all_rays(t_container *content) {
    ray_info(content);
}

int draw_game(t_container *content) {
    let_player_move(content);
    clear_map_after_player(content);
    draw_map(content);
    drawing_plr(content);
    cast_all_rays(content);
    mlx_put_image_to_window(content->src.mlx, content->src.win, content->src.img, 0, 0);
    return (0);
}

void start_the_play(t_container *content) {
    mlx_res_init(content);
    draw_map(content);
    mlx_put_image_to_window(content->src.mlx, content->src.win, content->src.img, 0, 0);
    mlx_hook(content->src.win, 17, 0, ft_close, content);
    mlx_hook(content->src.win, 2, 1L << 0, key_action, content);
    mlx_hook(content->src.win, 3, 1L << 1, key_back, content);
    mlx_loop_hook(content->src.mlx, draw_game, content);
    mlx_loop(content->src.mlx);
}
