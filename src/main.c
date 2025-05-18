#include "../inc/cub3d.h"

void ft_error(char *err)
{
	perror(err);
	exit(1);
}

void is_file_ext_valid(char *filename)
{
    int	len;

	len = ft_strlen(filename);
	if (len >= 4)
	{
		if (ft_strcmp(filename + len - 4, ".cub") != 0)
			ft_error("invalid file name");
	}
	else
		ft_error("invalid file name");
}

int main(int ac, char **av)
{
    (void)av;
    if (ac != 2)
        return (write(2,"Invalid number of arrguments!\n", 31), 1);
    is_file_ext_valid(av[1]);
    return (0);
}