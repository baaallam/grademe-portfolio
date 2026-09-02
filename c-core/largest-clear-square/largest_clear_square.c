#include <unistd.h>
#include <stdlib.h>

typedef struct s_map
{
	int		rows;
	int		cols;
	char	empty;
	char	obstacle;
	char	fill;
	char	**grid;
}	t_map;

static void	map_error(void)
{
	write(1, "map error\n", 10);
}

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	is_printable(char c)
{
	return (c >= 32 && c <= 126);
}

static int	read_line(char **line, int *len)
{
	char	c;
	char	*tmp;
	int		size;
	int		n;
	int		ret;

	size = 16;
	n = 0;
	*line = malloc(size);
	if (!*line)
		return (0);
	ret = read(0, &c, 1);
	while (ret > 0 && c != '\n')
	{
		if (n + 1 >= size)
		{
			size *= 2;
			tmp = realloc(*line, size);
			if (!tmp)
			{
				free(*line);
				*line = NULL;
				return (0);
			}
			*line = tmp;
		}
		(*line)[n++] = c;
		ret = read(0, &c, 1);
	}
	if (ret < 0 || (ret == 0 && n == 0))
	{
		free(*line);
		*line = NULL;
		return (0);
	}
	(*line)[n] = '\0';
	*len = n;
	return (1);
}

static int	parse_header(char *s, t_map *map)
{
	int	i;
	int	rows;

	i = 0;
	if (!is_digit(s[i]))
		return (0);
	rows = 0;
	while (is_digit(s[i]))
	{
		rows = rows * 10 + s[i] - '0';
		i++;
	}
	if (rows <= 0 || s[i] != ' ')
		return (0);
	map->rows = rows;
	i++;
	if (!is_printable(s[i]) || s[i] == ' ')
		return (0);
	map->empty = s[i++];
	if (s[i++] != ' ')
		return (0);
	if (!is_printable(s[i]) || s[i] == ' ')
		return (0);
	map->obstacle = s[i++];
	if (s[i++] != ' ')
		return (0);
	if (!is_printable(s[i]) || s[i] == ' ')
		return (0);
	map->fill = s[i++];
	if (s[i] != '\0')
		return (0);
	if (map->empty == map->obstacle
		|| map->empty == map->fill
		|| map->obstacle == map->fill)
		return (0);
	return (1);
}

static int	read_map(t_map *map)
{
	char	*line;
	int		len;
	int		r;
	int		c;

	map->grid = malloc(sizeof(char *) * map->rows);
	if (!map->grid)
		return (0);
	r = 0;
	map->cols = 0;
	while (r < map->rows)
	{
		if (!read_line(&line, &len) || len == 0)
			return (0);
		if (r == 0)
			map->cols = len;
		if (len != map->cols)
		{
			free(line);
			return (0);
		}
		c = 0;
		while (c < len)
		{
			if (line[c] != map->empty && line[c] != map->obstacle)
			{
				free(line);
				return (0);
			}
			c++;
		}
		map->grid[r] = line;
		r++;
	}
	return (1);
}

static void	free_map(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (i < map->rows)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

static int	square_size(t_map *map, int row, int col)
{
	int	max;
	int	size;
	int	r;
	int	c;

	max = map->rows - row;
	if (map->cols - col < max)
		max = map->cols - col;
	size = 1;
	while (size <= max)
	{
		r = row;
		while (r < row + size)
		{
			c = col;
			while (c < col + size)
			{
				if (map->grid[r][c] != map->empty)
					return (size - 1);
				c++;
			}
			r++;
		}
		size++;
	}
	return (max);
}

static void	find_largest(t_map *map, int *br, int *bc, int *bs)
{
	int	row;
	int	col;
	int	size;

	*br = 0;
	*bc = 0;
	*bs = 0;
	row = 0;
	while (row < map->rows)
	{
		col = 0;
		while (col < map->cols)
		{
			if (map->grid[row][col] == map->empty)
			{
				size = square_size(map, row, col);
				if (size > *bs)
				{
					*bs = size;
					*br = row;
					*bc = col;
				}
			}
			col++;
		}
		row++;
	}
}

static void	fill_square(t_map *map, int row, int col, int size)
{
	int	r;
	int	c;

	r = row;
	while (r < row + size)
	{
		c = col;
		while (c < col + size)
		{
			map->grid[r][c] = map->fill;
			c++;
		}
		r++;
	}
}

static void	print_map(t_map *map)
{
	int	row;

	row = 0;
	while (row < map->rows)
	{
		write(1, map->grid[row], map->cols);
		write(1, "\n", 1);
		row++;
	}
}

int	main(int argc, char **argv)
{
	t_map	map;
	char	*header;
	int		header_len;
	int		best_row;
	int		best_col;
	int		best_size;

	(void)argv;
	map.grid = NULL;
	if (argc != 1)
		return (1);
	if (!read_line(&header, &header_len))
	{
		map_error();
		return (1);
	}
	if (!parse_header(header, &map))
	{
		free(header);
		map_error();
		return (1);
	}
	free(header);
	if (!read_map(&map))
	{
		free_map(&map);
		map_error();
		return (1);
	}
	find_largest(&map, &best_row, &best_col, &best_size);
	if (best_size > 0)
		fill_square(&map, best_row, best_col, best_size);
	print_map(&map);
	free_map(&map);
	return (0);
}
