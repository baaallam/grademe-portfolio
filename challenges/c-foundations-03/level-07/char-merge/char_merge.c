#include <unistd.h>

static int	seen(char *s, int len, char c)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char	seen_chars[256];
	int		count;
	int		i;
	unsigned char	c;

	if (argc != 3)
	{
		write(1, "wrong number of arguments\n", 26);
		return (0);
	}
	count = 0;
	i = 0;
	while (argv[2][i])
	{
		c = (unsigned char)argv[2][i];
		if (!seen(seen_chars, count, c))
		{
			seen_chars[count++] = c;
			write(1, &argv[2][i], 1);
		}
		i++;
	}
	i = 0;
	while (argv[1][i])
	{
		c = (unsigned char)argv[1][i];
		if (!seen(seen_chars, count, c))
		{
			seen_chars[count++] = c;
			write(1, &argv[1][i], 1);
		}
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
