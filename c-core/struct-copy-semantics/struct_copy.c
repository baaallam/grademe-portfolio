#include <stddef.h>

typedef struct record
{
	int	id;
	int	score;
	char	*name;
} record;

record	record_with_id(record src, int id)
{
	record	out;

	out = src;
	out.id = id;
	return (out);
}
