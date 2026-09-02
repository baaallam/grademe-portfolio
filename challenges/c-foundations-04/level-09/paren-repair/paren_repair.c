#include <unistd.h>

static int	g_len;

static void	print_solution(char *s)
{
	write(1, s, g_len);
	write(1, "\n", 1);
}

static void	solve(char *s, int pos, int balance, int left, int right)
{
	if (pos == g_len)
	{
		if (balance == 0 && left == 0 && right == 0)
			print_solution(s);
		return ;
	}
	if (s[pos] == '(')
	{
		if (left > 0)
		{
			s[pos] = ' ';
			solve(s, pos + 1, balance, left - 1, right);
		}
		s[pos] = '(';
		solve(s, pos + 1, balance + 1, left, right);
	}
	else
	{
		if (right > 0)
		{
			s[pos] = ' ';
			solve(s, pos + 1, balance, left, right - 1);
		}
		if (balance > 0)
		{
			s[pos] = ')';
			solve(s, pos + 1, balance - 1, left, right);
		}
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	balance;
	int	left;
	int	right;

	if (argc != 2)
		return (1);
	g_len = 0;
	while (argv[1][g_len])
	{
		if (argv[1][g_len] != '(' && argv[1][g_len] != ')')
			return (1);
		g_len++;
	}

	left = 0;
	right = 0;
	balance = 0;
	i = 0;
	while (i < g_len)
	{
		if (argv[1][i] == '(')
			balance++;
		else if (balance > 0)
			balance--;
		else
			right++;
		i++;
	}
	balance = 0;
	i = g_len - 1;
	while (i >= 0)
	{
		if (argv[1][i] == ')')
			balance++;
		else if (balance > 0)
			balance--;
		else
			left++;
		i--;
	}

	{
		char	buf[10000];

		i = 0;
		while (i < g_len && i < 9999)
		{
			buf[i] = argv[1][i];
			i++;
		}
		if (i != g_len)
			return (1);
		solve(buf, 0, 0, left, right);
	}
	return (0);
}

