
int	digit_sum(int n)
{
	long nb;
	nb = n;
	int sum  = 0;
	if (nb < 0){
		nb = -nb;
	}

	while(nb > 0)
	{
      sum = sum + nb % 10;
		nb = nb / 10;
	}
	return (sum);
}
