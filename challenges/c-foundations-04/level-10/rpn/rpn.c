#include <unistd.h>

static void	put_error(void)
{
	write(1, "Error\n", 6);
}

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	is_operator(char c)
{
	return (c == '+' || c == '-' || c == '*'
		|| c == '/' || c == '%');
}

static int	parse_int(char **s, int *n)
{
	long	value;
	int		sign;

	value = 0;
	sign = 1;
	if (**s == '-')
	{
		sign = -1;
		(*s)++;
	}
	if (!is_digit(**s))
		return (0);
	while (is_digit(**s))
	{
		value = value * 10 + (**s - '0');
		if ((sign == 1 && value > 2147483647L)
			|| (sign == -1 && value > 2147483648L))
			return (0);
		(*s)++;
	}
	*n = (int)(value * sign);
	return (1);
}

static void	put_number(int n)
{
	char	buf[12];
	int		i;
	unsigned int	value;

	i = 11;
	buf[i--] = '\n';
	if (n < 0)
	{
		value = (unsigned int)(-(n + 1)) + 1;
		while (value > 0)
		{
			buf[i--] = '0' + value % 10;
			value /= 10;
		}
		buf[i--] = '-';
	}
	else
	{
		value = (unsigned int)n;
		if (value == 0)
			buf[i--] = '0';
		while (value > 0)
		{
			buf[i--] = '0' + value % 10;
			value /= 10;
		}
	}
	write(1, buf + i + 1, 11 - i);
}

int	main(int argc, char **argv)
{
	int		stack[1024];
	int		top;
	int		a;
	int		b;
	int		result;
	char	*s;

	if (argc != 2)
	{
		put_error();
		return (0);
	}
	top = 0;
	s = argv[1];
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (!*s)
			break ;
		if (is_digit(*s) || (*s == '-' && is_digit(s[1])))
		{
			if (top >= 1024 || !parse_int(&s, &result))
			{
				put_error();
				return (0);
			}
			stack[top++] = result;
		}
		else if (is_operator(*s) && (s[1] == ' ' || s[1] == '\0'))
		{
			if (top < 2)
			{
				put_error();
				return (0);
			}
			b = stack[--top];
			a = stack[--top];
			if ((*s == '/' || *s == '%') && b == 0)
			{
				put_error();
				return (0);
			}
			if (*s == '+')
				result = a + b;
			else if (*s == '-')
				result = a - b;
			else if (*s == '*')
				result = a * b;
			else if (*s == '/')
				result = a / b;
			else
				result = a % b;
			stack[top++] = result;
			s++;
		}
		else
		{
			put_error();
			return (0);
		}
		if (*s && *s != ' ')
		{
			put_error();
			return (0);
		}
	}
	if (top != 1)
	{
		put_error();
		return (0);
	}
	put_number(stack[0]);
	return (0);
}
