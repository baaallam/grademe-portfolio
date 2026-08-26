#include <unistd.h>

int	main(int argc, char **argv)
{
	int i = 0;
	int n = 1; 
	if(argc!=2){
    	write(1,"wrong number of arguments\n",26);
	 	return(0);
	}
	while(n<argc){
		while(argv[1][i]!='\0'){
			if(argv[1][i]>='a' && argv[1][i]<='z' && argv[1][i]=='n'){
				write(1,&argv[1][i],1);
				write(1,"\n",1);
				return(0);
			}
			i++;
		}
		n++;
	}
    write(1,"\n",1);
	return (0);
}
