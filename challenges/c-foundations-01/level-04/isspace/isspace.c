int	isspace(char c)
{
	int i ;
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' )
	 i = 1;
  else 
	i = 0;
return (i);
}
