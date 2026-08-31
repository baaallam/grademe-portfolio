int	sum_range(const int *first, const int *last)
{
	int	sum;

	sum = 0;
	while (first < last)
	{
		sum += *first;
		first++;
	}
	return (sum);
}
