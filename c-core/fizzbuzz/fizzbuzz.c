#include <unistd.h>
void putnbr(int nb){
    long n;
    char c;
    n = nb;
    if (n >  9 )
    {
        putnbr(n/10);
    }
    c = (n % 10) + '0';
    write(1,&c,1);
}
int main(void)
{
    int i = 1;
    while (i <= 100)
    {
        if ((i % 3 == 0) && (i % 5 == 0))
        {
            write(1, "FizzBuzz", 8);
        }
        else if (i % 3 == 0)
        {
            write(1, "Fizz", 4);
        }
        else if (i % 5 == 0)
        {
            write(1, "Buzz", 4);
        }
        else
        {
           putnbr(i);
        }
        write(1, "\n", 1);
        i++;
    }
    return (0);
}