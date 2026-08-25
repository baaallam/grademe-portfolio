#include <unistd.h>

int	main(int argc, char **argv)
{
	   int i =0;
	   int n = 0;
	if (argc>0){
		write(1,"\n",1);
	}
	while (argv[n][i]!='\0'){
       i++;
	}
	return (0);
}
