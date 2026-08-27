#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	height;
	int	row;
	int	spaces;
	int	hashes;

	if (argc != 2)
	{
		write(1, "wrong number of arguments\n", 26);
		return (0);
	}
	height = atoi(argv[1]);
	row = 0;
	while (row < height)
	{
		spaces = height - row - 1;
		hashes = 2 * row + 1;
		while (spaces > 0)
		{
			write(1, " ", 1);
			spaces--;
		}
		while (hashes > 0)
		{
			write(1, "#", 1);
			hashes--;
		}
		write(1, "\n", 1);
		row++;
	}
	return (0);
}
