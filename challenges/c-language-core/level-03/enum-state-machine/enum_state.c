enum state
{
	IDLE,
	RUNNING,
	PAUSED,
	DONE,
	FAILED
};

enum event
{
	START,
	PAUSE,
	RESUME,
	FINISH,
	ERROR
};

enum state	next_state(enum state current, enum event e)
{
	if (current == DONE || current == FAILED)
		return (current);
	if (current == IDLE && e == START)
		return (RUNNING);
	if (current == RUNNING && e == PAUSE)
		return (PAUSED);
	if (current == RUNNING && e == FINISH)
		return (DONE);
	if (current == RUNNING && e == ERROR)
		return (FAILED);
	if (current == PAUSED && e == RESUME)
		return (RUNNING);
	if (current == PAUSED && e == ERROR)
		return (FAILED);
	return (current);
}
