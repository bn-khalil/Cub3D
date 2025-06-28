#ifndef CUB3D_H
#define CUB3D_H

#include <fcntl.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <float.h>
#define MINIMAP_WIDTH 200
#define MINIMAP_HEIGHT 200
#define MINIMAP_BORDER 5
#define MINIMAP_CELL_SIZE 8 
#define PIXEL_SIZE 32
#define PLR PIXEL_SIZE / 3
#define PI 3.14159265
#define FOV (60.0 * (PI / 180.0))
#define WALL_COL_WIDH 1
#define  MAP_RATIO 0.8
#define MAP_W 1080
#define MAP_H 720
#define C_COLOR 0x87CEEB
#define F_COLOR   0x434230
#define M_CELL 8
#define M_MAP_S 200
#define M_M_X 10
#define M_M_Y 10
#define M_CELL 8
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
  float wall_hight;
  int is_ray_left;
  int is_ray_right;
  int is_ray_up;
  int is_ray_down;
  int is_hit_horizontal;
  int is_hit_vertical;
  int was_vertical;
  char *wall_dir;
  int wall_strip_high;
  int wall_top_pixel;
  int botm_pixel;
  int c;
  int f;
} t_ray;

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

typedef struct s_minimap
{
    int minimap_radius; 
    int player_map_x;
    int player_map_y;
    float offset_x;
    float offset_y;
    int       minimap_cell_x; // Variable for minimap cell x-coordinate
    int       minimap_cell_y; // Variable for minimap cell y-coordinate

}	t_minimap;

typedef struct s_line_params{

  int dx;
  int dy;
  int end_x;
  int end_y;
  int steps;
  float xInc; 
  float yInc; 
  float x;
  float y;
} t_line_params;

typedef struct s_sprite {
  void *img;
  char *buffer;
  int width;
  int height;
  int size_l;
  int nbits;
  int endian;
  int draw_x;
  int draw_y;
  int px;
  int py;
  unsigned int color;
  unsigned int rgb;
} t_sprite;

typedef struct s_door{
    int color;
    int w;
    int h;
    int ind;
    int size_l;
    int n_bits;
    void *door_img;
    char *door_data;
    t_config *texture;
} t_door;

typedef struct s_container {
  int fd_map;
  int number_of_newlines;
  int map_w;
  int map_h;
  char **file_content;
  char **map;
  char **configues;
  char **rgb;
  char *filename;
  char *line;
  t_config *confs;
  unsigned int floor_color;
  unsigned int ceiling_color;
  int player_pos;
  int num_rays;
  t_src src;
  t_plr plr;
  t_ray *rays;
  int old_mouse_x;
  int mouse_press;
  int fix_mouse_x;
  int open_door;
  int sprite_switcher;
  t_minimap *minimap;
  t_line_params *line_par;
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
int mouse_detection(int x, int y, void *data);
int mouse_press(int button, int x, int y, void *data);
int mouse_release(int button, int x, int y, void *data);
float get_vector_dis(t_container *content, float nex_x, float nex_y);
void get_the_smallest(t_ray *ray, float ray_angle, float player_angle);
void	get_the_horizantal(t_container *content, int i);
void	get_vertical(t_container *content, int i);
int mod(int a, int b);
void ray_info(t_container *content);
void	ft_free_2d(char **str);
void ft_free_all(t_container *content);
void put_player_map(t_container *content);
void drawlinedda_minimap(int x, int y, int color, t_container *content);
void initiale_minimap(t_container *content);
void ft_free_all(t_container *content);
int	 is_map_chars(char c);
char *ft_complete(t_container *content, char *str);
void	door_check(t_container *content, int i, int j);
void	player_pos_check(t_container *content, int i, int j);
void	map_sides_check(t_container *content, int i, int j);
void	map_items_check(t_container *content, int i, int j);
int	is_map_covered_with_walls(int x, int y, t_container *content);
void ft_texture_loading(t_container *content, t_sprite *spr);
void put_texture_to_screen(t_container *content, t_sprite *spr);
void draw_sprite_hands(t_container *content);
void draw_ceilling_floor(t_container *content, t_ray ray, int i);
void draw_texture_on_screen(t_container *content, t_ray ray, t_door door, int i);
void draw_door(t_container *content, t_door door, t_ray ray, int i);

#endif
