#include <unistd.h>

static int	contains(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	seen_before(char *str, int end, char c)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	i;
	int	count;
	char	out[256];

	if (argc != 3)
	{
		write(1, "wrong number of arguments\n", 26);
		return (0);
	}
	i = 0;
	count = 0;
	while (argv[2][i])
	{
		if (contains(argv[1], argv[2][i])
			&& !seen_before(out, count, argv[2][i]))
		{
			out[count++] = argv[2][i];
			write(1, &argv[2][i], 1);
		}
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
