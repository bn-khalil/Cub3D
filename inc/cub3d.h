#ifndef CUB3D_H
#define CUB3D_H

#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_container {
    int fd_map;
    int number_of_newlines;
    char **map;
    char *filename;
    char *line;
} t_container;

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
int	    ft_strcmp(char *s1, char *s2);
void	ft_putnbr(int nb);
char	*get_next_line(t_container *content);
void    get_and_init_map(t_container *content);
void    ft_error(char *err, t_container *content);
char	**ft_split(char *s, char c);


#endif