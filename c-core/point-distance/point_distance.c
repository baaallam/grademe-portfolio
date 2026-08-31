typedef struct point
{
	int	x;
	int	y;
} point;

long	point_distance2(point a, point b)
{
	long	dx;
	long	dy;

	dx = (long)a.x - (long)b.x;
	dy = (long)a.y - (long)b.y;
	return (dx * dx + dy * dy);
}
