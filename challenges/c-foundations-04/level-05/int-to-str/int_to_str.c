#include <stdlib.h>

char	*int_to_str(int n)
{
	char			*str;
	unsigned int	num;
	int				len;
	int				negative;

	negative = 0;
	if (n < 0)
		negative = 1;
	if (n < 0)
		num = (unsigned int)(-(n + 1)) + 1;
	else
		num = (unsigned int)n;
	len = 1;
	while (num >= 10)
	{
		num /= 10;
		len++;
	}
	num = (n < 0) ? (unsigned int)(-(n + 1)) + 1 : (unsigned int)n;
	str = malloc(sizeof(char) * (len + negative + 1));
	if (!str)
		return (NULL);
	str[len + negative] = '\0';
	while (len > 0)
	{
		str[negative + len - 1] = '0' + (num % 10);
		num /= 10;
		len--;
	}
	if (negative)
		str[0] = '-';
	return (str);
}
