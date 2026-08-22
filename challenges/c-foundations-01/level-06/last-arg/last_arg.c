#include <unistd.h>

int	main(int argc, char **argv)
{
	int i = 0;
	int n;
	n =argc - 1;
	if (argc == 1) {
		write (1,"wrong number of arguments\n",26);
		return (0);
	}
	while (argv[n][i]!='\0' && argv[n][i]!=32){ 
		write (1,&argv[n][i],1);
		i++;
	}
	write (1,"\n",1);
	return (0);
}
