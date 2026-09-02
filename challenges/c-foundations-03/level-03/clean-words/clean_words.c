#include <unistd.h>

static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	main(int argc, char **argv)
{
	int	i;
	int	in_word;
	int	space_pending;
	char	c;

	if (argc != 2)
	{
		write(1, "wrong number of arguments\n", 26);
		return (0);
	}
	i = 0;
	in_word = 0;
	space_pending = 0;
	while (argv[1][i])
	{
		c = argv[1][i];
		if (is_space(c))
		{
			if (in_word)
				space_pending = 1;
		}
		else
		{
			if (space_pending)
				write(1, " ", 1);
			write(1, &c, 1);
			in_word = 1;
			space_pending = 0;
		}
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
