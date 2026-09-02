#include <unistd.h>
#include <stdlib.h>

static int	ft_atoi(char *s, int *valid)
{
	long	n;
	int		i;

	i = 0;
	n = 0;
	if (!s[0])
	{
		*valid = 0;
		return (0);
	}
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
		{
			*valid = 0;
			return (0);
		}
		n = n * 10 + (s[i] - '0');
		if (n > 2147483647)
		{
			*valid = 0;
			return (0);
		}
		i++;
	}
	return ((int)n);
}

static void	draw(int *board, int w, int h)
{
	char	c;
	int		row;
	int		col;
	int		pen;

	row = 0;
	col = 0;
	pen = 0;
	while (read(0, &c, 1) > 0)
	{
		if (c == 'p')
		{
			pen = !pen;
			if (pen)
				board[row * w + col] = 1;
		}
		else if (c == 'u')
		{
			if (row > 0)
				row--;
			if (pen)
				board[row * w + col] = 1;
		}
		else if (c == 'd')
		{
			if (row < h - 1)
				row++;
			if (pen)
				board[row * w + col] = 1;
		}
		else if (c == 'l')
		{
			if (col > 0)
				col--;
			if (pen)
				board[row * w + col] = 1;
		}
		else if (c == 'r')
		{
			if (col < w - 1)
				col++;
			if (pen)
				board[row * w + col] = 1;
		}
	}
}

static int	count_neighbors(int *board, int w, int h, int row, int col)
{
	int	count;
	int	r;
	int	c;

	count = 0;
	r = row - 1;
	while (r <= row + 1)
	{
		c = col - 1;
		while (c <= col + 1)
		{
			if (!(r == row && c == col)
				&& r >= 0 && r < h && c >= 0 && c < w)
				count += board[r * w + c];
			c++;
		}
		r++;
	}
	return (count);
}

static void	simulate(int *board, int *next, int w, int h, int iterations)
{
	int	i;
	int	count;
	int	size;

	size = w * h;
	while (iterations > 0)
	{
		i = 0;
		while (i < size)
		{
			count = count_neighbors(board, w, h, i / w, i % w);
			if (board[i])
				next[i] = (count == 2 || count == 3);
			else
				next[i] = (count == 3);
			i++;
		}
		i = 0;
		while (i < size)
		{
			board[i] = next[i];
			i++;
		}
		iterations--;
	}
}

static void	print_board(int *board, int w, int h)
{
	char	c;
	int		row;
	int		col;

	row = 0;
	while (row < h)
	{
		col = 0;
		while (col < w)
		{
			if (board[row * w + col])
				c = '@';
			else
				c = '.';
			write(1, &c, 1);
			col++;
		}
		write(1, "\n", 1);
		row++;
	}
}

int	main(int argc, char **argv)
{
	int	w;
	int	h;
	int	iterations;
	int	valid;
	int	*board;
	int	*next;

	if (argc != 4)
		return (1);

	valid = 1;
	w = ft_atoi(argv[1], &valid);
	h = ft_atoi(argv[2], &valid);
	iterations = ft_atoi(argv[3], &valid);
	if (!valid || w <= 0 || h <= 0)
		return (1);

	board = calloc(w * h, sizeof(int));
	next = calloc(w * h, sizeof(int));
	if (!board || !next)
	{
		free(board);
		free(next);
		return (1);
	}

	draw(board, w, h);
	simulate(board, next, w, h, iterations);
	print_board(board, w, h);

	free(board);
	free(next);
	return (0);
}
