#include "../../inc/cub3d.h"
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

    for (int i = 0; i <= steps; i++) {
        print_pxt((int)round(x), (int)round(y), color, content);
        x += xInc;
        y += yInc;
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
  if (content->plr.std_direction == 'E')
    content->plr.r_angle = 0;
  if (content->plr.std_direction == 'W')
    content->plr.r_angle = PI;
  if (content->plr.std_direction == 'S')
    content->plr.r_angle = PI / 2;
  if (content->plr.std_direction == 'N')
    content->plr.r_angle = 3 * PI / 2;
  content->plr.r_speed = 1 * (PI / 180);

}

void mlx_res_init(t_container *content) {
  init_player(content);
  content->src.mlx = mlx_init();
  content->src.win =
      mlx_new_window(content->src.mlx, content->map_w * PIXEL_SIZE,
                     content->map_h * PIXEL_SIZE, "Cub3D");
  content->src.img =
      mlx_new_image(content->src.mlx, content->map_w * PIXEL_SIZE,
                    content->map_h * PIXEL_SIZE);
  content->src.buffer_pos =
      mlx_get_data_addr(content->src.img, &content->src.pixel_bits_number,
                        &content->src.len_with_pixels, &content->src.endian);
}

int ft_close(t_container *content) {
  // free and close window and mlx connections
  (void)content;
  exit(0);
  return (0);
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
  return (0);
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
  return (0);
}

int is_wall(float x, float y, t_container *content) {
  int i = (int)(x / PIXEL_SIZE);
  int j = (int)(y / PIXEL_SIZE);

  if (i < 0 || j < 0 || i >= content->map_w || j >= content->map_h)
    return 1;

  if (!content->map || !content->map[j])
    return 1; // guard null pointers

  if (content->map[j][i] == '1')
    return 1;

  return 0;
}

int ft_is_collision(float x, float y, t_container *content) {
  if (is_wall(x, y, content) || is_wall(x + (float)PLR, y, content) ||
      is_wall(x, y + (float)PLR, content) ||
      is_wall(x + (float)PLR, y + (float)PLR, content)) {
    return 1;
  }
  return 0;
}

void let_player_move(t_container *content) {
    // Normalize angle first
    content->plr.r_angle = fix_angle(content->plr.r_angle);

    // Handle rotation
    if (content->plr.rotate_left)
        content->plr.r_angle -= content->plr.r_speed;
    if (content->plr.rotate_right)
        content->plr.r_angle += content->plr.r_speed;
    
    // Normalize again after rotation
    content->plr.r_angle = fix_angle(content->plr.r_angle);

    // Get precise trig values with epsilon checks
    float cos_an = cos(content->plr.r_angle);
    float sin_an = sin(content->plr.r_angle);
    
    // Snap to exact cardinal directions if very close
    if (fabs(cos_an) < 0.0001) cos_an = 0;
    if (fabs(sin_an) < 0.0001) sin_an = 0;

    // Movement calculations remain the same
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

void drawing_rays_angle(t_container *content, float angle) {
  float ray_x = content->plr.x + (float)PLR / 2;
  float ray_y = content->plr.y + (float)PLR / 2;
  float cos_an = cos(angle);
  float sin_an = sin(angle);
  int length = 30;
  int i;

  for (i = 0; i < length; i++) {
    float x = ray_x + cos_an * i;
    float y = ray_y + sin_an * i;
    print_pxt(x, y, 0x00FF00, content);
  }
}
/* void ray_info(t_container *content) */
/* { */
/*   int i = -1; */
/*   int columes = 0; */
/*   int num_ray = 1; */
/*   int is_hit_horsental = 0; */
/*   float ray_angle = content->plr.r_angle - (FOV / 2); */
/*    */
/*   while (++i < num_ray) { */
/*     content->rays[i].ray_angle = ray_angle; */
/*     content->rays[i].is_ray_down = ray_angle > 0 && ray_angle < PI; */
/*     content->rays[i].is_ray_up = !content->rays[i].is_ray_down;  */
/*     content->rays[i].is_ray_right = ray_angle < (PI / 2) || ray_angle > 1.5 * PI; */
/*     content->rays[i].is_ray_left = !content->rays[i].is_ray_right; */
/*     content->rays[i].y_intersept = floor(content->plr.y / PIXEL_SIZE) * PIXEL_SIZE; */
/*      */
/*     if (content->rays[i].is_ray_down) { */
/*         content->rays[i].y_intersept += PIXEL_SIZE; */
/*     } */
/*     else { */
/*         content->rays[i].y_intersept += 0; */
/*     } */
/*      */
/*     content->rays[i].x_intersept = content->plr.x + (content->rays[i].y_intersept - content->plr.y) / tan(ray_angle); */
/*     content->rays[i].y_step = PIXEL_SIZE; */
/*      */
/*     if (content->rays[i].is_ray_up) { */
/*         content->rays[i].y_step *= -1; */
/*     } */
/*      */
/*     content->rays[i].x_step = PIXEL_SIZE / tan(ray_angle); */
/*      */
/*     if (content->rays[i].is_ray_left && content->rays[i].x_step > 0) { */
/*         content->rays[i].x_step *= -1; */
/*     } */
/*        */
/*     if (content->rays[i].is_ray_right && content->rays[i].x_step < 0) { */
/*         content->rays[i].x_step *= -1; */
/*     } */
/*      */
/*     content->rays[i].next_h_x_touch = content->rays[i].x_intersept; */
/*     content->rays[i].next_h_y_touch = content->rays[i].y_intersept; */
/*      */
/*     if (content->rays[i].is_ray_up) { */
/*       content->rays[i].next_h_y_touch--; */
/*     } */
/*      */
/*     while (content->rays[i].next_h_x_touch >= 0 &&  */
/*            content->rays[i].next_h_x_touch <= content->map_w * PIXEL_SIZE && */
/*            content->rays[i].next_h_y_touch >= 0 &&  */
/*            content->rays[i].next_h_y_touch <= content->map_h * PIXEL_SIZE) */
/*     { */
/*       if (is_wall(content->rays[i].next_h_x_touch, content->rays[i].next_h_y_touch, content)) { */
/*         is_hit_horsental = 1; */
/*         content->rays[i].hit_x = content->rays[i].next_h_x_touch; */
/*         content->rays[i].hit_y = content->rays[i].next_h_y_touch; */
/*         drawLineDDA(content->plr.x, content->plr.y, content->rays[i].hit_x, content->rays[i].hit_y, 0x00FF00, content); */
/*         break; */
/*       } */
/*       else { */
/*         content->rays[i].next_h_x_touch += content->rays[i].x_step; */
/*         content->rays[i].next_h_y_touch += content->rays[i].y_step; */
/*       } */
/*     } */
/*        */
/*     ray_angle += FOV / num_ray; */
/*     columes++; */
/*   } */
/* } */
void ray_info(t_container *content)
{
  int i = -1;
  int columes = 0;
  int num_ray = 1;
  int is_hit_horsental = 0;
  float ray_angle = content->plr.r_angle - (FOV / 2);
  while (++i < num_ray) {
    //geting the inte first intersection horisantal x and y//
    content->rays[i].ray_angle = fix_angle(ray_angle);
    content->rays[i].is_ray_down = ray_angle > 0 && ray_angle < PI;
    content->rays[i].is_ray_up = !content->rays[i].is_ray_down; 
    content->rays[i].is_ray_right = ray_angle < (PI / 2) || ray_angle > 1.5 * PI;
    content->rays[i].is_ray_left = !content->rays[i].is_ray_right;
    content->rays[i].y_intersept = floor(content->plr.y / PIXEL_SIZE) * PIXEL_SIZE;
    content->rays[i].x_intersept = content->plr.x + (content->rays[i].y_intersept - content->plr.y) / tan(ray_angle);
    if (content->rays[i].is_ray_down)
      content->rays[i].y_intersept += PIXEL_SIZE;
    content->rays[i].y_step = PIXEL_SIZE;
    if (content->rays[i].is_ray_up)
        content->rays[i].y_step *= -1;
    content->rays[i].x_step = PIXEL_SIZE  / tan(ray_angle);
    if (content->rays[i].is_ray_left && content->rays[i].x_step > 0)
        content->rays[i].x_step *= -1;
      
    if (content->rays[i].is_ray_right && content->rays[i].x_step < 0)
        content->rays[i].x_step *= -1;
    content->rays[i].next_h_x_touch = content->rays[i].x_intersept;
    content->rays[i].next_h_y_touch = content->rays[i].y_intersept;
    if (content->rays[i].is_ray_up)
      content->rays[i].next_h_y_touch--;
  while (content->rays[i].next_h_x_touch >= 0 && 
           content->rays[i].next_h_x_touch <= content->map_w * PIXEL_SIZE &&
           content->rays[i].next_h_y_touch >= 0 && 
           content->rays[i].next_h_y_touch <= content->map_h * PIXEL_SIZE)
    {
      if (is_wall(content->rays[i].next_h_x_touch, content->rays[i].next_h_y_touch, content)) {
        is_hit_horsental = 1;
        content->rays[i].hit_x = content->rays[i].next_h_x_touch;
        content->rays[i].hit_y = content->rays[i].next_h_y_touch;
        drawLineDDA(content->plr.x, content->plr.y, content->rays[i].hit_x, content->rays[i].hit_y, 0x00FF00, content);
        break;
      }
      else {
        content->rays[i].next_h_x_touch += content->rays[i].x_step;
        content->rays[i].next_h_y_touch += content->rays[i].y_step;
      }
    }
      
    ray_angle += FOV / num_ray;
    columes++;
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
  mlx_put_image_to_window(content->src.mlx, content->src.win, content->src.img,
                          0, 0);
  return (0);
}

void start_the_play(t_container *content) {
  mlx_res_init(content);
  draw_map(content);
  mlx_put_image_to_window(content->src.mlx, content->src.win, content->src.img,
                          0, 0);
  mlx_hook(content->src.win, 17, 0, ft_close, content);
  mlx_hook(content->src.win, 2, 1L << 0, key_action, content);
  mlx_hook(content->src.win, 3, 1L << 1, key_back, content);
  mlx_loop_hook(content->src.mlx, draw_game, content);
  mlx_loop(content->src.mlx);
}
