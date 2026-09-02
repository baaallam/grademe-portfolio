#include <unistd.h>

static char	to_upper(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

static char	to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	main(int argc, char **argv)
{
	int		i;
	int		start;
	char	c;

	if (argc < 2)
	{
		write(1, "wrong number of arguments\n", 26);
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		start = 1;
		while (*argv[i])
		{
			c = *argv[i];
			if (c == ' ' || c == '\t')
				start = 1;
			else if (start)
			{
				c = to_upper(c);
				start = 0;
			}
			else
				c = to_lower(c);
			write(1, &c, 1);
			argv[i]++;
		}
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
