#include <stdlib.h>

static int	is_delim(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

static int	count_words(char *str, char *charset)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && is_delim(*str, charset))
			str++;
		if (*str)
		{
			count++;
			while (*str && !is_delim(*str, charset))
				str++;
		}
	}
	return (count);
}

char	**split(char *str, char *charset)
{
	char	**result;
	int		words;
	int		i;
	int		len;
	int		j;

	words = count_words(str, charset);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*str)
	{
		while (*str && is_delim(*str, charset))
			str++;
		if (!*str)
			break ;
		len = 0;
		while (str[len] && !is_delim(str[len], charset))
			len++;
		result[i] = malloc(sizeof(char) * (len + 1));
		if (!result[i])
			return (NULL);
		j = 0;
		while (j < len)
		{
			result[i][j] = str[j];
			j++;
		}
		result[i][j] = '\0';
		i++;
		str += len;
	}
	result[i] = NULL;
	return (result);
}
