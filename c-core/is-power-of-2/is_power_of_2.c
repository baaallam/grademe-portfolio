
int is_power_of_2(unsigned int n)
{
	unsigned int p = 2;
	if (n==1){
		return(1);
	}
	if (n==0){
		return(0);
	}
	while(p <= n)
	{
		if (p==n)
			return(1);
		p = p * 2;
	}
	return (0);
}
