#include "ft_ssl.h"

// TODO decide the arcitecture of buffer

reg32		buffer[17];

int			init_md5_hash(t_hash *hash)
{
	hash->a = 0x67452301;
	hash->b = 0xEFCDAB89;
	hash->c = 0x98BADCFE;
	hash->d = 0x10325476;
	return (0);
}

int		fill_msg_len(size_t msg_len, char *buffer)
{
	buffer[56] = (msg_len * 8) >> (8 * 0) & A;
	buffer[57] = (msg_len * 8) >> (8 * 1) & A;
	buffer[58] = (msg_len * 8) >> (8 * 2) & A;
	buffer[59] = (msg_len * 8) >> (8 * 3) & A;
	buffer[60] = (msg_len * 8) >> (8 * 4) & A;
	buffer[61] = (msg_len * 8) >> (8 * 5) & A;
	buffer[62] = (msg_len * 8) >> (8 * 6) & A;
	buffer[63] = (msg_len * 8) >> (8 * 7) & A;
	return (0);
}

size_t	fill_buffer_from_str(char *str, char *buffer)
{
	static char		*str_char_ptr = NULL;
	static int		return_append_array = 0;
	static char 	append_buffer[64];
	static size_t	msg_len = 0;
	size_t			i;

	if (!str_char_ptr)
		str_char_ptr = str;
	if (return_append_array)
	{
		memcpy(buffer, append_buffer, 64);
		return_append_array = 0;
		msg_len = 0;
		bzero(append_buffer, 64);
		str_char_ptr = NULL;
	}
	i = 0;
	while (str_char_ptr[i] && i < 64)
	{
		buffer[i] = str_char_ptr[i];
		++i;
	}
	msg_len += i;
	if (i == 64)
		return (0);
	bzero(buffer + i, 64 - i);
	buffer[i] = 0x80;
	if (i >= 56)
	{
		bzero(append_buffer, 64);
		fill_msg_len(msg_len, append_buffer);
		return_append_array = 1;
		return (0);
	}
	else
	{
		fill_msg_len(msg_len, buffer);
		return_append_array = 0;
		msg_len = 0;
		bzero(append_buffer, 64);
		str_char_ptr = NULL;
		return (1);
	}
}

size_t	fill_buffer_from_stream(int fd, char *buffer)
{
	static char			append_buffer[64];
	static int			return_append_array = 0;
	static size_t		msg_len = 0;
	size_t				read_len;

	if (return_append_array == 1)
	{
		memcpy(buffer, append_buffer, 64);
		close(fd);
		return_append_array = 0;
		msg_len = 0;
		bzero(append_buffer, 64);
		return (1);
	}
	read_len = read(fd, buffer, MD5_BUFFER_SIZE);
	msg_len += read_len;
	if (read_len == 64)
		return (0);
	else
	{
		bzero(buffer + read_len, 64 - read_len);
		buffer[read_len] = 0x80;
		if (read_len >= 56)
		{
			bzero(append_buffer, 64);
			fill_msg_len(msg_len, append_buffer);
			return_append_array = 1;
			return (0);
		}
		else
		{
			fill_msg_len(msg_len, buffer);
			close(fd);
			return_append_array = 0;
			msg_len = 0;
			bzero(append_buffer, 64);
			return (1);
		}
	}
}

int 	fill_buffer(char *str, char *buffer, int flags)
{
	static int	file_fd = 0;
	size_t		ret;

	if (flags & FLAG_S)
	{
		return (fill_buffer_from_str(str, buffer));
	}
	else if (flags & FLAG_P)
	{
		ret = fill_buffer_from_stream(0, buffer);
		write(1, buffer, strlen(buffer));
		return (ret);
	}
	else
	{
		if (!file_fd)
			file_fd = open(str, O_RDONLY);
		if (file_fd == -1)
			return (-1);
		return (fill_buffer_from_stream(file_fd, buffer));
	}
}

void		*md5(char *str, int flags)
{
	t_hash		hsh;
	int			fb_return;

	init_md5_hash(&hsh);
	bzero(buffer, 64);
	while (1)
	{
		hsh.aa = hsh.a;
		hsh.bb = hsh.b;
		hsh.cc = hsh.c;
		hsh.dd = hsh.d;
		fb_return = fill_buffer(str, (char *)buffer, flags);
		R1;
		R2;
		R3;
		R4;
		hsh.a += hsh.aa;
		hsh.b += hsh.bb;
		hsh.c += hsh.cc;
		hsh.d += hsh.dd;
		if (fb_return == 1)
			break ;
		else if (fb_return == -1)
		{
			flags |= FLAG_FILEERROR;
			break ;
		}
	}
	print_md5(hsh, str, flags);
	return (NULL);
}