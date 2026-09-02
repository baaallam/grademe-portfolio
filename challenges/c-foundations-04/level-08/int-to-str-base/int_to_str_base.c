#include <stdlib.h>

char	*int_to_str_base(int value, int base)
{
	unsigned int	n;
	unsigned int	tmp;
	char			*str;
	int				len;
	int				negative;

	if (base < 2 || base > 16)
		return (NULL);
	negative = (value < 0 && base == 10);
	if (negative)
		n = (unsigned int)(-(value + 1)) + 1;
	else
		n = (unsigned int)value;
	tmp = n;
	len = 1;
	while (tmp >= (unsigned int)base)
	{
		tmp /= (unsigned int)base;
		len++;
	}
	str = malloc((size_t)len + negative + 1);
	if (!str)
		return (NULL);
	str[len + negative] = '\0';
	while (len > 0)
	{
		len--;
		if (n % (unsigned int)base < 10)
			str[len + negative] = '0' + n % (unsigned int)base;
		else
			str[len + negative] = 'a'
				+ (n % (unsigned int)base - 10);
		n /= (unsigned int)base;
	}
	if (negative)
		str[0] = '-';
	return (str);
}
