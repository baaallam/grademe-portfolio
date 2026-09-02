#include <unistd.h>

static void	put_number(int n)
{
	char	buf[12];
	int		i;

	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	i = 11;
	while (n > 0)
	{
		buf[--i] = '0' + (n % 10);
		n /= 10;
	}
	write(1, buf + i, 11 - i);
}

static int	parse_number(char *s)
{
	int	n;

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
	int	n;
	int	i;

	if (argc != 2)
	{
		write(1, "wrong number of arguments\n", 26);
		return (0);
	}
	n = parse_number(argv[1]);
	i = 1;
	while (i <= 9)
	{
		put_number(i);
		write(1, " x ", 3);
		put_number(n);
		write(1, " = ", 3);
		put_number(i * n);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
