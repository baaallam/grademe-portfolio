#include <unistd.h>

static void	put_hex(unsigned int n)
{
	char	c;

	if (n >= 16)
		put_hex(n / 16);
	c = "0123456789abcdef"[n % 16];
	write(1, &c, 1);
}

static unsigned int	parse_number(char *s)
{
	unsigned int	n;

	n = 0;
	while (*s >= '0' && *s <= '9')
	{
		n = n * 10 + (*s - '0');
		s++;
	}
	return (n);
}

int	main(int argc, char **argv)
{
	unsigned int	n;

	if (argc != 2)
	{
		write(1, "wrong number of arguments\n", 26);
		return (0);
	}
	n = parse_number(argv[1]);
	put_hex(n);
	write(1, "\n", 1);
	return (0);
}
