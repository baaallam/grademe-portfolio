#include <unistd.h>

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

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	n;

	i = 0;
	sign = 1;
	n = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * sign);
}

int	main(int argc, char **argv)
{
	int	i;
	int	sum;

	sum = 0;
	i = 1;
	while (i < argc)
	{
		sum += ft_atoi(argv[i]);
		i++;
	}
	putnbr(sum);
	write(1, "\n", 1);
	return (0);
}
