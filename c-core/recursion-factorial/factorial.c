
int	factorial(int  f )
{
	int z = 0;
	if (f == z) {
		return(1);
	}
	if (f < z) {
		return (-1);
	}
	return (f * factorial(f - 1));
}
