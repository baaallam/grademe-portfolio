#include <unistd.h>
#include <stdlib.h>

static int	abs_int(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

static int	is_safe(int *board, int col, int row)
{
	int	i;

	i = 0;
	while (i < col)
	{
		if (board[i] == row
			|| abs_int(board[i] - row) == col - i)
			return (0);
		i++;
	}
	return (1);
}

static void	print_solution(int *board, int n)
{
	int		i;
	char	c;

	i = 0;
	while (i < n)
	{
		c = board[i] + '0';
		if (board[i] >= 10)
		{
			if (board[i] >= 100)
			{
				c = (board[i] / 100) + '0';
				write(1, &c, 1);
				c = ((board[i] / 10) % 10) + '0';
				write(1, &c, 1);
			}
			else
			{
				c = (board[i] / 10) + '0';
				write(1, &c, 1);
			}
			c = (board[i] % 10) + '0';
		}
		write(1, &c, 1);
		if (i + 1 < n)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

static void	solve(int *board, int n, int col)
{
	int	row;

	if (col == n)
	{
		print_solution(board, n);
		return ;
	}
	row = 0;
	while (row < n)
	{
		if (is_safe(board, col, row))
		{
			board[col] = row;
			solve(board, n, col + 1);
		}
		row++;
	}
}

int	main(int argc, char **argv)
{
	int	n;
	int	*board;

	if (argc != 2)
		return (1);

	n = atoi(argv[1]);
	if (n < 0)
		return (0);

	if (n == 0)
	{
		write(1, "\n", 1);
		return (0);
	}

	board = malloc(sizeof(int) * n);
	if (!board)
		return (0);

	solve(board, n, 0);
	free(board);
	return (0);
}
