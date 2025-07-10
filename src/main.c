#include "../include/cub3d.h"

static void	error_exit(const char *msg)
{
	write(STDERR_FILENO, "Error\n", 6);
	while (*msg)
	{
		write(STDERR_FILENO, msg, 1);
		++msg;
	}
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

static int	has_cub_extension(const char *file)
{
	int	i;

	if (!file)
		return (0);
	i = 0;
	while (file[i])
		++i;
	if (i < 5)
		return (0);
	return (file[i - 4] == '.' && file[i - 3] == 'c' && file[i - 2] == 'u' \
		&& file[i - 1] == 'b');
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		error_exit("Usage: ./cub3D <map.cub>");
	if (!has_cub_extension(argv[1]))
		error_exit("Map file must have .cub extension");
	if (access(argv[1], F_OK) < 0)
       error_exit("Map file not found");
	if (cub3d_run(argv[1]) != 0)
		error_exit("cub3D terminated unexpectedly");
	return (EXIT_SUCCESS);
}