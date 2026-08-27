#include <unistd.h>

int	main(int argc, char **argv)
{
	(void) **argv;
	int n = 1;
	int c = 0;
	char s;
	char v;
	if  (argc == 1)
	{
		write(1,"0\n",2);
		return(0);
	}
	while(n<argc)
	{
		n++;
		c++;
	}
	if (c <10)
	{
		s = c + '0';
		write(1,&s,1);
		write(1,"\n",1);
	}
	if (c == 10)
	{
		s = 49;
		v = 48;
		write(1,&s,1);
		write(1,&v,1);
		write(1,"\n",1);
	}

	return (0);
}
