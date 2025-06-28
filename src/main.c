#include "../inc/cub3d.h"

void	is_file_ext_valid(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len >= 4)
	{
		if (ft_strcmp(filename + len - 4, ".cub") != 0)
			ft_error("there is not file with this name \n", NULL);
	}
	else
		ft_error("invalid file name", NULL);
}

int	main(int ac, char **av)
{
	t_container	content;

	if (ac != 2)
		return (write(2, "Invalid number of arrguments!\n", 31), 1);
	is_file_ext_valid(av[1]);
	ft_memset(&content, 0, sizeof(t_container));
	content.filename = av[1];
	get_and_init_map(&content);
	start_the_play(&content);
	ft_free_all(&content);
	return (0);
}
