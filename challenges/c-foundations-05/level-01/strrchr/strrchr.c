#include <stddef.h>

char	*strrchr(char *str, int c)
{
	char	*last;

	last = NULL;
	while (*str != '\0')
	{
		if (*str == (char)c)
			last = str;
		str++;
	}
	if (*str == (char)c)
		last = str;
	return (last);
}
