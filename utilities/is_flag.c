int			is_flag(const char *str)
{
	if (str && str[0] == '-' && str[1] != '\0')
		return (1);
	return (0);
}