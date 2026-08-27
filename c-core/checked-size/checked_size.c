#include <stddef.h>
#include <stdint.h>

int	checked_size(size_t n, size_t size, size_t *out)
{
	if (size != 0 && n > SIZE_MAX / size)
		return (0);
	*out = n * size;
	return (1);
}
