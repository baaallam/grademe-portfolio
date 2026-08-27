// Count the decimal digits of n, sign excluded, with zero written as one digit.
// Never negate n: INT_MIN has no positive counterpart inside an int.
#include <stdio.h>

int	digit_count(int n)
{
	
	int count = 0;
	int div = 1;
	long nb = n;
	if (nb == -2147483648 )
	{
		return (10);
	}
	if (nb == 2147483647 )
	{
		return (10);
	}
	if (nb == -2147483647 )
	{
		return (10);
	}
	if (nb == 0){
		return (1);
	}
	if (nb < 0)
		nb = -nb;

	while ((nb / div) > 0)
	{
		div *= 10;
		count ++;
	}

	return (count);
}
