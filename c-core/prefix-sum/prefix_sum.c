#include <stddef.h>

// out[i] holds the sum of a[0] through a[i], and a stays read-only.
// The running total is a long because it can outgrow an int.
void	prefix_sum(const int *a, size_t n, long *out)
{
	size_t	i;
	long	sum;

	i = 0;
	sum = 0;
	while (i < n)
	{
		sum += a[i];
		out[i] = sum;
		i++;
	}
}
