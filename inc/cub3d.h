#ifndef CUB3D_H
#define CUB3D_H

#include <fcntl.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <float.h>
#define MINIMAP_WIDTH 200    // Fixed width in pixels
#define MINIMAP_HEIGHT 200   // Fixed height
#define MINIMAP_BORDER 5     // Border width
#define MINIMAP_CELL_SIZE 8 // How many pixels per map cell
#define PIXEL_SIZE 32
#define PLR PIXEL_SIZE / 3
#define PI 3.14159265
#define FOV (60.0 * (PI / 180.0))
#define WALL_COL_WIDH 1
#define  MAP_RATIO 0.2

#ifdef __APPLE__
#define KEY_ESC 53
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_W 13
#define KEY_LEFT 123
#define KEY_RIGHT 124

#elif defined(__linux__)
#define KEY_ESC 65307
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_W 119
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_UP 65362
#define KEY_DOWN 65364
#else
#endif

typedef struct s_ray {
  float wall_hit_x;
  float wall_hit_y;
  float next_h_y_touch;
  float next_h_x_touch;
  float next_v_y_touch;
  float next_v_x_touch;
  float ray_angle;
  float x_intersept;
  float y_intersept;
  float x_step;
  float y_step;
  float distance;
  float ver_distance;
  float horiz_distance;
  float horiz_hit_x;
  float horiz_hit_y;
  float ver_hit_x;
  float ver_hit_y;
  int is_ray_left;
  int is_ray_right;
  int is_ray_up;
  int is_ray_down;
  int is_hit_horizontal;
  int is_hit_vertical;
  int was_vertical;
  char *wall_dir;
} t_ray;


typedef struct s_config {
  char *id;
  char *value;
  int fd;
  int txr_w;
  int txr_h;
  void *img;
  char *buffer_pos;
  int endian;
  int len_with_pixels;
  int pixel_bits_number;
  struct s_config *next;
} t_config;

typedef struct s_plr {
  float x;
  float y;
  char std_direction;
  int up;
  int down;
  int left;
  int right;
  float radius;
  float r_angle;
  float speed;
  float r_speed;
  int rotate_left;
  int rotate_right;
} t_plr;

typedef struct s_src {
  void *mlx;
  void *win;
  void *img;
  char *buffer_pos;
  int endian;
  int len_with_pixels;
  int pixel_bits_number;
} t_src;

typedef struct s_container {
  int fd_map;
  int number_of_newlines;
  int map_w;
  int map_h;
  char **file_content;
  char **map;
  char **configues;
  char *filename;
  char *line;
  t_config *confs;
  char *floor_color;
  char *ceiling_color;
  int player_pos;
  int num_rays;
  t_src src;
  t_plr plr;
  t_ray *rays;
} t_container;

int ft_strlen(const char *s);
int ft_isdigit(int c);
char *ft_strjoin(char *s1, char *s2);
int ft_strcmp(char *s1, char *s2);
void ft_putnbr(int nb);
char *get_next_line(t_container *content);
void get_and_init_map(t_container *content);
void ft_error(char *err, t_container *content);
char **ft_split(char *s, char c, int skip_separator);
void parsing_map_content(t_container *content, int start);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_substr(char const *s, unsigned int start, size_t len);
void configure_parsing(t_container *content);
char *ft_strdup(const char *s1);
void ft_configue(t_config **lst, t_config *new);
int ft_atoi(const char *str);
t_config *ft_new_config(t_container *content, int fd_file, char *dir,
                        char *path);
void configue_direction_parsing(t_container *content, char *direction,
                                char *path);
void check_rgb_format(char *str, t_container *content);
void check_color_separator(char *color_form, t_container *content);
void configue_rgb_parsing(t_container *content, char *color, int flag);
void print_list(t_config *head);
int get_number_newlines(char *str);
char *get_next_line(t_container *content);
void get_width_and_height(t_container *content);
void map_printer(char **map);
int is_paces(char *str);
void start_the_play(t_container *content);
void drawing_plr(t_container *content);
void draw_m(int x, int y, int color, t_container *content);
int draw_map(t_container *content);
void draw_clean(int x, int y, int color, t_container *content);
void clear_map_after_player(t_container *content);
void print_pxt(int x, int y, int color, t_container *content);
int draw_game(t_container *content);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strtrim(char *s1, char *set);
int key_action(int keycode, t_container *content);
int key_back(int keycode, t_container *content);
int ft_close(t_container *content);
int ft_is_collision(float x, float y, t_container *content);
void let_player_move(t_container *content);
int is_wall(float x, float y, t_container *content);
void render_minimap(t_container *content);
float fix_angle(float angle);
void texture_init(t_container *content);

#endif
