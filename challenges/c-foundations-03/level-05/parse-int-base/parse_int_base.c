static int	get_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

int	parse_int_base(const char *str, int base)
{
	int	sign;
	int	result;
	int	digit;

	if (base < 2 || base > 16)
		return (0);
	while (*str <= 32)
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	digit = get_digit(*str);
	while (digit >= 0 && digit < base)
	{
		result = result * base + digit;
		str++;
		digit = get_digit(*str);
	}
	return (result * sign);
}
