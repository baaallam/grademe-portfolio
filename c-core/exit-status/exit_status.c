#include <limits.h>
#include <unistd.h>

int	ft_atoi(char *str, int *error)
{
	int		i;
	int		sign;
	long	n;

	i = 0;
	sign = 1;
	n = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
	{
		*error = 1;
		return (0);
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		if (n * sign > INT_MAX || n * sign < INT_MIN)
		{
			*error = 2;
			return (0);
		}
		i++;
	}
	if (str[i] != '\0')
	{
		*error = 1;
		return (0);
	}
	return ((int)(n * sign));
}

void	putnbr(int nbr)
{
	long	n;
	char	c;

	n = nbr;
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		putnbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

int	main(int argc, char **argv)
{
	int	i;
	int	error;
	int	n;
	long	sum;

	if (argc < 2)
		return (1);
	sum = 0;
	i = 1;
	while (i < argc)
	{
		error = 0;
		n = ft_atoi(argv[i], &error);
		if (error == 1)
			return (2);
		if (error == 2)
			return (3);
		sum += n;
		if (sum > INT_MAX || sum < INT_MIN)
			return (3);
		i++;
	}
	putnbr((int)sum);
	write(1, "\n", 1);
	return (0);
}
