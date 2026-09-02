#include <unistd.h>
#include <stdarg.h>

static int	put_str(const char *s)
{
	int	len;

	if (!s)
		s = "(null)";
	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
	return (len);
}

static int	put_dec(int n)
{
	char			buf[12];
	int				i;
	unsigned int	nb;
	int				count;

	count = 0;
	i = 11;
	if (n < 0)
	{
		write(1, "-", 1);
		count++;
		nb = (unsigned int)(-(n + 1)) + 1;
	}
	else
		nb = (unsigned int)n;
	if (nb == 0)
	{
		write(1, "0", 1);
		return (count + 1);
	}
	while (nb > 0)
	{
		buf[--i] = '0' + nb % 10;
		nb /= 10;
	}
	write(1, buf + i, 11 - i);
	return (count + 11 - i);
}

static int	put_hex(unsigned int n)
{
	char			buf[8];
	const char		*base;
	int				i;

	base = "0123456789abcdef";
	i = 8;
	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	while (n > 0)
	{
		buf[--i] = base[n % 16];
		n /= 16;
	}
	write(1, buf + i, 8 - i);
	return (8 - i);
}

int	mini_printf(const char *fmt, ...)
{
	va_list			ap;
	int				i;
	int				count;
	int				c;
	char			*s;

	va_start(ap, fmt);
	i = 0;
	count = 0;
	while (fmt[i])
	{
		if (fmt[i] != '%')
		{
			write(1, &fmt[i], 1);
			count++;
		}
		else
		{
			i++;
			if (fmt[i] == 'c')
			{
				c = va_arg(ap, int);
				write(1, &c, 1);
				count++;
			}
			else if (fmt[i] == 's')
			{
				s = va_arg(ap, char *);
				count += put_str(s);
			}
			else if (fmt[i] == 'd')
				count += put_dec(va_arg(ap, int));
			else if (fmt[i] == 'x')
				count += put_hex(va_arg(ap, unsigned int));
			else if (fmt[i] == '%')
			{
				write(1, "%", 1);
				count++;
			}
			else
			{
				write(1, "%", 1);
				count++;
				if (fmt[i])
				{
					write(1, &fmt[i], 1);
					count++;
				}
			}
		}
		if (fmt[i])
			i++;
	}
	va_end(ap);
	return (count);
}
