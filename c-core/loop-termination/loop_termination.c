#include <stddef.h>

size_t	count_steps(unsigned int start)
{
	unsigned int	value;
	size_t			steps;

	value = start;
	steps = 0;
	while (value != 0)
	{
		steps++;
		value = value / 2;
	}
	return (steps);
}
