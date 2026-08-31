#include <stddef.h>

void	reverse_int(int *a, size_t n)
{
	size_t	i;
	int		tmp;

	i = 0;
	while (i < n / 2)
	{
		tmp = a[i];
		a[i] = a[n - 1 - i];
		a[n - 1 - i] = tmp;
		i++;
	}
}
