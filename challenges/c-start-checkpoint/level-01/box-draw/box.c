#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	width;
	int	height;
	int	x;
	int	y;

	if (argc != 3)
	{
		write(1, "wrong number of arguments\n", 26);
		return (0);
	}
	width = atoi(argv[1]);
	height = atoi(argv[2]);
	if (width <= 0 || height <= 0)
		return (0);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if ((y == 0 || y == height - 1)
				&& (x == 0 || x == width - 1))
				write(1, "+", 1);
			else if (y == 0 || y == height - 1)
				write(1, "-", 1);
			else if (x == 0 || x == width - 1)
				write(1, "|", 1);
			else
				write(1, " ", 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
	return (0);
}
