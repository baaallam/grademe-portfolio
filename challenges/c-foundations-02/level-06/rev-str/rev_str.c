char	*rev_str(char *str)
{
	int		left;
	int		right;
	char	tmp;

	left = 0;
	right = 0;
	while (str[right])
		right++;
	right--;
	while (left < right)
	{
		tmp = str[left];
		str[left] = str[right];
		str[right] = tmp;
		left++;
		right--;
	}
	return (str);
}
