#include <unistd.h>

int	main(int argc, char **argv)
{
	int		col;
	int		n;
	char	c;

	if (argc != 2)
	{
		write(1, "wrong number of arguments\n", 26);
		return (0);
	}
	col = 0;
	while (*argv[1])
	{
		if (*argv[1] == ' ')
		{
			n = 8 - col % 8;
			while (n > 0)
			{
				write(1, " ", 1);
				n--;
			}
			col += 8 - col % 8;
		}
		else
		{
			c = *argv[1];
			write(1, &c, 1);
			col++;
		}
		argv[1]++;
	}
	write(1, "\n", 1);
	return (0);
}
