int	ft_isalnum(int c)
{
	if (c <= 'z' && c >= 'a')
		return (1);
	else if (c <= 'Z' && c >= 'A')
		return (1);
	else if (c <= '9' && c >= '0')
		return (1);
	else
		return (0);
}
