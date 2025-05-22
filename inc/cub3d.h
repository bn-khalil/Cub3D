#ifndef CUB3D_H
#define CUB3D_H

#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_config {
    char *id;
    char *value;
    int fd;
    struct s_config *next;
} t_config;

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
} t_container;

int	ft_strlen(const char *s);
int     ft_isdigit(int c);
char	*ft_strjoin(char *s1, char *s2);
int	    ft_strcmp(char *s1, char *s2);
void	ft_putnbr(int nb);
char	*get_next_line(t_container *content);
void    get_and_init_map(t_container *content);
void    ft_error(char *err, t_container *content);
char	**ft_split(char *s, char c, int skip_separator);
void    parsing_map_content(t_container *content, int start);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void    configure_parsing(t_container *content);
char	*ft_strdup(const char *s1);
void	ft_configue(t_config **lst, t_config *new);
int	    ft_atoi(const char *str);
t_config	*ft_new_config(t_container *content, int fd_file, char *dir, char *path);
void configue_direction_parsing(t_container *content, char *direction, char *path);
void check_rgb_format(char *str, t_container *content);
void check_color_separator(char *color_form, t_container *content);
void configue_rgb_parsing(t_container *content, char *color, int flag);
void print_list(t_config *head);
int	get_number_newlines(char *str);
char	*get_next_line(t_container *content);
void get_width_and_height(t_container *content);
void map_printer(char **map);
int is_paces(char *str);




#endif