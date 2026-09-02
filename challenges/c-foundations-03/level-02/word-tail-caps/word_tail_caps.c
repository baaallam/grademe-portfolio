#include <unistd.h>

static int	is_letter(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static char	to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

static char	to_upper(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

static void	process_word(char *s, int start, int end)
{
	int		i;
	int		last;
	char	c;

	last = -1;
	i = start;
	while (i < end)
	{
		if (is_letter(s[i]))
			last = i;
		i++;
	}
	i = start;
	while (i < end)
	{
		c = s[i];
		if (is_letter(c))
		{
			if (i == last)
				c = to_upper(c);
			else
				c = to_lower(c);
		}
		write(1, &c, 1);
		i++;
	}
}

static void	process_arg(char *s)
{
	int	start;
	int	i;

	start = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t')
		{
			process_word(s, start, i);
			write(1, &s[i], 1);
			start = i + 1;
		}
		i++;
	}
	process_word(s, start, i);
	write(1, "\n", 1);
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc < 2)
	{
		write(1, "wrong number of arguments\n", 26);
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		process_arg(argv[i]);
		i++;
	}
	return (0);
}
