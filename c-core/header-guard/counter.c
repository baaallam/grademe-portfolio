#include "counter.h"

void	counter_reset(counter *c)
{
	c->value = 0;
}

void	counter_add(counter *c, int amount)
{
	c->value += amount;
}

int	counter_value(counter *c)
{
	return (c->value);
}
