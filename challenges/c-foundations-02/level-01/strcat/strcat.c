#include <unistd.h>
char	*strcat(char *dst, const char *src)
{
	int i = 0;
	int j = 0;
	if (src[i]=='\0'){
		return (dst);
	}
	while (dst[j]!='\0'){
		j++;
	}
	while (src[i]!='\0'){
         dst[j] = src[i];
		i++;
		j++;
	}
	dst[j]='\0';
	return (dst);
}
