#ifndef COUNTER_H
# define COUNTER_H

typedef struct counter
{
	int	value;
} counter;

void	counter_reset(counter *c);
void	counter_add(counter *c, int amount);
int		counter_value(counter *c);

#endif
