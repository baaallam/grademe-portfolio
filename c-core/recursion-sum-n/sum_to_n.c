// sum_to_n(n) is n + sum_to_n(n - 1), with sum_to_n(0) equal to 0.
// A negative n is invalid: return -1.
int	sum_to_n(int n)
{
	long nb;
	nb = n;
	if (nb == 0 || nb == 1)
	{
		return (nb);
	}

	if (nb < 0){
		return (-1);
	}
	return (nb + sum_to_n(nb - 1));
}
