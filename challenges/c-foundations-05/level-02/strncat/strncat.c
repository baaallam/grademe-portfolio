char	*strncat(char *dst, const char *src, unsigned int n)
{
	char	*ret;
	unsigned int	i;

	ret = dst;
	while (*dst)
		dst++;
	i = 0;
	while (i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ret);
}
