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
} t_container;

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
int	    ft_strcmp(char *s1, char *s2);
void	ft_putnbr(int nb);
char	*get_next_line(t_container *content);
void    get_and_init_map(t_container *content);
void    ft_error(char *err, t_container *content);
char	**ft_split(char *s, char c);
void    parsing_map_content(t_container *content);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void    configure_parsing(t_container *content);
char	*ft_strdup(const char *s1);
void	ft_configue(t_config **lst, t_config *new);
t_config	*ft_new_config(t_container *content, int fd_file, char *dir, char *path);


#endif