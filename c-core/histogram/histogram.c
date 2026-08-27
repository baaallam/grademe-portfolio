#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	n;

	if (argc == 1)
	{
		write(1, "wrong number of arguments\n", 26);
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		n = atoi(argv[i]);
		while (n > 0)
		{
			write(1, "#", 1);
			n--;
		}
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
