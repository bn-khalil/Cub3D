#include "../../inc/cub3d.h"


t_config *get_texture_by_id(t_config *confs, const char *id) {
    while (confs) {
        if (ft_strncmp(confs->id, id, 2) == 0)
            return confs;
        confs = confs->next;
    }
    return NULL;
}



void set_ray_wall_dir(t_ray *ray, t_container *content)
{
    int map_x = (int)(ray->wall_hit_x / PIXEL_SIZE);
    int map_y = (int)(ray->wall_hit_y / PIXEL_SIZE);

    if (!ray->was_vertical && ray->ray_angle > M_PI && ray->ray_angle < 2 * M_PI)
        map_y -= 1;
    else if (ray->was_vertical && ray->ray_angle > M_PI_2 && ray->ray_angle < 3 * M_PI_2)
        map_x -= 1;

    char tile = content->map[map_y][map_x];
    if (content->open_door && tile == 'D')
    {
        float plr_map_x = content->plr.x / PIXEL_SIZE;
        float plr_map_y = content->plr.y / PIXEL_SIZE;
        float dx = (float)map_x + 0.5f - plr_map_x;
        float dy = (float)map_y + 0.5f - plr_map_y;
        float distance = sqrtf(dx*dx + dy*dy);
        float open_radius = 1.8f;

        if (distance < open_radius)
        {
            float plr_angle = content->plr.r_angle;
            float vx = cosf(plr_angle);
            float vy = sinf(plr_angle);
            float dot = (dx * vx + dy * vy) / (sqrtf(dx*dx + dy*dy) * sqrtf(vx*vx + vy*vy));
            if (dot > 0.5f)
                content->map[map_y][map_x] = 'P';
        }
    }

    tile = content->map[map_y][map_x];
    // Check 3x3 grid around hit tile for open doors
    float plr_map_x = content->plr.x / PIXEL_SIZE;
    float plr_map_y = content->plr.y / PIXEL_SIZE;
    float close_radius = 2.2f;
    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            int check_x = map_x + dx;
            int check_y = map_y + dy;
            if (check_x >= 0 && check_x < content->map_w && check_y >= 0 && check_y < content->map_h &&
                content->map[check_y][check_x] == 'P')
            {
                float dist_x = (float)check_x + 0.5f - plr_map_x;
                float dist_y = (float)check_y + 0.5f - plr_map_y;
                float distance = sqrtf(dist_x * dist_x + dist_y * dist_y);
                if (distance > close_radius)
                    content->map[check_y][check_x] = 'D';
            }
        }
    }

    tile = content->map[map_y][map_x];
    if (tile == 'D') {
        ray->wall_dir = "DO";
        return;
    }
    if (tile == 'P') {
        ray->wall_dir = "DO";
        return;
    }
    if (ray->was_vertical) {
        if (ray->ray_angle > M_PI_2 && ray->ray_angle < 3 * M_PI_2)
            ray->wall_dir = "WE";
        else
            ray->wall_dir = "EA";
    } else {
        if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
            ray->wall_dir = "NO";
        else
            ray->wall_dir = "SO";
    }
}

void convert_2d_to_3d(t_container *content)
{
    int i;
    t_ray ray;
    float distance_projection;
    float wall_hight;
    int color;
    int w;
    int h;
    int ind;
    int size_l;
    int n_bits;
    void *door_img = mlx_xpm_file_to_image(content->src.mlx, "./textures/d.xpm", &w, &h);
    char *door = mlx_get_data_addr(door_img, &size_l, &n_bits, &ind);

    i = -1;
    distance_projection = (MAP_W / 2.0f) / tan(FOV / 2.0f);
    while (++i < content->num_rays)
    {
        int c;
        int f;

        ray = content->rays[i];
        if (ray.distance < 0.1f)
            ray.distance = 0.1f;
        wall_hight = (PIXEL_SIZE / ray.distance) * distance_projection;
        int wall_strip_high = (int)wall_hight;
        int wall_top_pixel = (MAP_H / 2) - (wall_strip_high / 2);
        if (wall_top_pixel < 0)
            wall_top_pixel = 0;
        int botm_pixel = (MAP_H / 2) + (wall_strip_high / 2);
        if (botm_pixel > MAP_H)
            botm_pixel = MAP_H;

        c = -1;
        while (++c < wall_top_pixel)
            print_pxt(i * WALL_COL_WIDH, c, C_COLOR, content);
        f = botm_pixel;
        while (f < MAP_H)
        {
            print_pxt(i * WALL_COL_WIDH, f, F_COLOR, content);
            f++;
        }

        set_ray_wall_dir(&ray, content);
        t_config *texture = get_texture_by_id(content->confs, ray.wall_dir);
        if (!texture || !texture->buffer_pos)
        {
            for (int y = wall_top_pixel; y < botm_pixel; y++) {
                if (ray.wall_dir && ft_strcmp(ray.wall_dir, "DO") == 0)
                {
                    int t_x;
                    int t_y;
                    float r_r = (float)(y - (MAP_H / 2)) / wall_hight;
                    float relative_y = (0.5f + r_r) * h;
                    t_y = (int) relative_y;
                    if (t_y < 0)
                        t_y = 0;
                    if (t_y >= h)
                        t_y = h - 1;
                    if (ray.was_vertical)
                        t_x = mod((ray.wall_hit_y * w / PIXEL_SIZE), w);
                    else
                        t_x = mod((ray.wall_hit_x * w / PIXEL_SIZE), w);
                    unsigned int color = ((unsigned int*)door)[t_y * w + t_x];
                    print_pxt(i * WALL_COL_WIDH, y, color, content);
                }
            }
            continue;
        }
        int tex_x;
        if (ray.was_vertical)
            tex_x = mod((ray.wall_hit_y * texture->txr_w / PIXEL_SIZE), texture->txr_w);
        else
            tex_x = mod((ray.wall_hit_x * texture->txr_w / PIXEL_SIZE), texture->txr_w);

        float texture_scale = (float)texture->txr_h / wall_hight;
        for (int y = wall_top_pixel; y < botm_pixel; y++) {
            float relative_y = (float)(y - (MAP_H / 2)) / wall_hight;
            float texture_y = (0.5f + relative_y) * texture->txr_h;
            int tex_y = (int)texture_y;
            if (tex_y < 0)
                tex_y = 0;
            if (tex_y >= texture->txr_h)
                tex_y = texture->txr_h - 1;
            unsigned int color = ((unsigned int*)texture->buffer_pos)[tex_y * texture->txr_w + tex_x];
            print_pxt(i * WALL_COL_WIDH, y, color, content);
        }
    }
}

void draw_sprite_hands(t_container *content)
{
    void *img;
    char *buffer;
    int width, height;
    int size_l, nbits, endian;

    if (content->sprite_switcher < 10)
        img = mlx_xpm_file_to_image(content->src.mlx, "./textures/h6.xpm", &width, &height);
    else if (content->sprite_switcher < 15)
        img = mlx_xpm_file_to_image(content->src.mlx, "./textures/h5.xpm", &width, &height);
    else if (content->sprite_switcher < 25)
        img = mlx_xpm_file_to_image(content->src.mlx, "./textures/h4.xpm", &width, &height);
    else if (content->sprite_switcher < 30)
        img = mlx_xpm_file_to_image(content->src.mlx, "./textures/h3+.xpm", &width, &height);
    else if (content->sprite_switcher < 35)
        img = mlx_xpm_file_to_image(content->src.mlx, "./textures/h1.xpm", &width, &height);
    else
    {
        if (content->plr.up)
            img = mlx_xpm_file_to_image(content->src.mlx, "./textures/h4.xpm", &width, &height);
        else
            img = mlx_xpm_file_to_image(content->src.mlx, "./textures/h2.xpm", &width, &height);
    }
    if (!img)
    {
        printf("Failed to load hand sprite image \n");
        return;
    }

    buffer = mlx_get_data_addr(img, &nbits, &size_l, &endian);

    int screen_w = MAP_W;
    int screen_h = MAP_H;
    int draw_x = (screen_w - width) / 1.35;
    int draw_y = screen_h - height + 8;

    if (nbits != 32)
    {
        fprintf(stderr, "Unexpected pixel format: nbits = %d\n", nbits);
        mlx_destroy_image(content->src.mlx, img);
        return;
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            unsigned int color = ((unsigned int*)buffer)[y * (size_l / 4) + x];
            unsigned int rgb = color & 0x00FFFFFF;
            if (rgb != 0x000000)
            {
                int px = draw_x + x;
                int py = draw_y + y;
                if (px >= 0 && px < screen_w && py >= 0 && py < screen_h)
                    print_pxt(px, py, color, content);
            }
        }
    }
    mlx_destroy_image(content->src.mlx, img);
    content->sprite_switcher = (content->sprite_switcher + 1) % 450;
}

int draw_game(t_container *content) {
    let_player_move(content);
    ray_info(content);
    clear_map_after_player(content);
    convert_2d_to_3d(content);
    render_minimap(content);
    draw_sprite_hands(content);
    mlx_put_image_to_window(content->src.mlx, content->src.win, content->src.img, 0, 0);
    return (0);
}
