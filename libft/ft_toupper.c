char ft_toupper(const char c)
{
	if ('a' <= c && c <= 'z'){
		return c - 32;
	}
	return c;
}
