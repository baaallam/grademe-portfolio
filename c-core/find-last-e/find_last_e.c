#include <unistd.h>

int	main(int argc, char **argv)
{
	int  l = 0;	
	if (argc != 2){
		write(1,"e",1);
	} 
	
	if (argc == 2){ 
		while (argv[1][l])
			l++;
		l--;
		while (l >= 0)
		{
			if (argv[1][l] == 'e')
			{
				write(1,&argv[1][l],1);
				write(1,"\n",1);
				return (0);
			}
			l--;	
		}
 	}
	write(1,"\n",1);
	return (0);
}