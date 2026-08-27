#include <limits.h>

int	money_format(long cents, char *out)
{
	long	n;
	int		i;
	int		j;
	char	tmp[20];

	i = 0;
	j = 0;
	if (cents < 0)
	{
		out[j++] = '-';
		n = cents;
	}
	else
		n = -cents;
	if (n / 100 == 0)
		tmp[i++] = '0';
	else
	{
		n = n / 100;
		while (n < 0)
		{
			tmp[i++] = '0' - (n % 10);
			n /= 10;
		}
	}
	while (i > 0)
		out[j++] = tmp[--i];
	out[j++] = '.';
	if (cents < 0)
	{
		n = -(cents % 100);
	}
	else
	{
		n = cents % 100;
	}
	out[j++] = '0' + n / 10;
	out[j++] = '0' + n % 10;
	out[j] = '\0';
	return (j);
}
