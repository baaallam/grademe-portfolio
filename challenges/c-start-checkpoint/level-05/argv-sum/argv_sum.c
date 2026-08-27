#include <unistd.h>

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

void	putnbr(int n)
{
	long	nb;
	char	c;

	nb = n;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		putnbr(nb / 10);
	c = (nb % 10) + '0';
	write(1, &c, 1);
}

int	main(int argc, char **argv)
{
	int	i;
	int	sum;

	i = 1;
	sum = 0;
	while (i < argc)
	{
		sum += ft_atoi(argv[i]);
		i++;
	}
	putnbr(sum);
	write(1, "\n", 1);
	return (0);
}
