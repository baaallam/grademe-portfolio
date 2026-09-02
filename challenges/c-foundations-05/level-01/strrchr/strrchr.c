char	*strrchr(const char *s, int c)
{
	const char	*last;

	last = 0;
	while (1)
	{
		if (*s == (char)c)
			last = s;
		if (*s == '\0')
			break ;
		s++;
	}
	return ((char *)last);
}
