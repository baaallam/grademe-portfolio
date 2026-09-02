#include <unistd.h>

static int	atoi_simple(char *s)
{
	int	sign;
	int	n;

	sign = 1;
	n = 0;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		n = n * 10 + (*s - '0');
		s++;
	}
	return (n * sign);
}

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
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	while (n > 0)
	{
		buf[--i] = '0' + n % 10;
		n /= 10;
	}
	write(1, buf + i, 11 - i);
}

static void	print_subset(int *values, int *chosen, int count)
{
	int	i;
	int	first;

	i = 0;
	first = 1;
	while (i < count)
	{
		if (chosen[i])
		{
			if (!first)
				write(1, " ", 1);
			put_number(values[i]);
			first = 0;
		}
		i++;
	}
	write(1, "\n", 1);
}

static void	search(int *values, int *chosen, int count,
		int pos, int sum, int target)
{
	if (pos == count)
	{
		if (sum == target)
			print_subset(values, chosen, count);
		return ;
	}
	chosen[pos] = 1;
	search(values, chosen, count, pos + 1,
		sum + values[pos], target);
	chosen[pos] = 0;
	search(values, chosen, count, pos + 1,
		sum, target);
}

int	main(int argc, char **argv)
{
	int	values[1024];
	int	chosen[1024];
	int	count;
	int	target;
	int	i;

	if (argc < 3)
		return (1);
	target = atoi_simple(argv[1]);
	count = argc - 2;
	if (count > 1024)
		return (1);
	i = 0;
	while (i < count)
	{
		values[i] = atoi_simple(argv[i + 2]);
		chosen[i] = 0;
		i++;
	}
	search(values, chosen, count, 0, 0, target);
	return (0);
}

