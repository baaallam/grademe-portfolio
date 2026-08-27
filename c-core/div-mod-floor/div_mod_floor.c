void	div_mod_floor(int a, int b, int *q, int *r)
{
	*q = a / b;
	*r = a % b;
	if (*r < 0)
	{
		if (b > 0)
			*q = *q - 1;
		else
			*q = *q + 1;
		if (b > 0)
			*r = *r + b;
		else
			*r = *r - b;
	}
}
