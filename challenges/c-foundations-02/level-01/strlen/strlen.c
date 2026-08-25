#include <unistd.h>

int	strlen(const char *s)
{
	unsigned int i = 0;
	if (s[0]=='\0'){
		return (0);
	}
	while (s[i]!='\0'){
		i++;
	}
	return (i);
}
