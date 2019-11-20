# define BASE64BUF_LEN 64

void		*base64(char *str, int flags)
{
	return (NULL);
}

void 		*encode_fd_to_base64(int fd)
{
	return (NULL);
}

void		*encode_str_to_base64(char *str)
{
	t_reg32		tmp;
	char		buf[BASE64BUF_LEN];
	size_t 		i;

	i = 0;
	while (/* есть что обсчитывать */)
	{
		tmp = (t_reg32)str[i];
		i += 3;
	}
}
