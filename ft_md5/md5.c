#include "ft_ssl.h"

reg32		buffer[16];

# define A 0b11111111
# define B 0b1111


char*		raw_md5(t_hash hsh)
{
	char	*buf;

	buf = (char *)malloc(33);

	buf[0] = hex_arr[hsh.a >> 4 & B];
	buf[1] = hex_arr[hsh.a >> 0 & B];
	buf[2] = hex_arr[hsh.a >> 12 & B];
	buf[3] = hex_arr[hsh.a >> 8 & B];
	buf[4] = hex_arr[hsh.a >> 20 & B];
	buf[5] = hex_arr[hsh.a >> 16 & B];
	buf[6] = hex_arr[hsh.a >> 28 & B];
	buf[7] = hex_arr[hsh.a >> 24 & B];
	//---
	buf[8] = hex_arr[hsh.b >> 4 & B];
	buf[9] = hex_arr[hsh.b >> 0 & B];
	buf[10] = hex_arr[hsh.b >> 12 & B];
	buf[11] = hex_arr[hsh.b >> 8 & B];
	buf[12] = hex_arr[hsh.b >> 20 & B];
	buf[13] = hex_arr[hsh.b >> 16 & B];
	buf[14] = hex_arr[hsh.b >> 28 & B];
	buf[15] = hex_arr[hsh.b >> 24 & B];
	//---
	buf[16] = hex_arr[hsh.c >> 4 & B];
	buf[17] = hex_arr[hsh.c >> 0 & B];
	buf[18] = hex_arr[hsh.c >> 12 & B];
	buf[19] = hex_arr[hsh.c >> 8 & B];
	buf[20] = hex_arr[hsh.c >> 20 & B];
	buf[21] = hex_arr[hsh.c >> 16 & B];
	buf[22] = hex_arr[hsh.c >> 28 & B];
	buf[23] = hex_arr[hsh.c >> 24 & B];
	//---
	buf[24] = hex_arr[hsh.d >> 4 & B];
	buf[25] = hex_arr[hsh.d >> 0 & B];
	buf[26] = hex_arr[hsh.d >> 12 & B];
	buf[27] = hex_arr[hsh.d >> 8 & B];
	buf[28] = hex_arr[hsh.d >> 20 & B];
	buf[29] = hex_arr[hsh.d >> 16 & B];
	buf[30] = hex_arr[hsh.d >> 28 & B];
	buf[31] = hex_arr[hsh.d >> 24 & B];

	buf[32] = 0;
	return (buf);
}

void		print_md5(t_hash hsh, char *str, int flags)
{
	char	*out;

	if (flags & FLAG_FILEERROR)
	{
		out = nstrjoin(3, "md5: ", str,
				": No such file or directory or it is directory\n");
		write(1, out, strlen(out));
	}
	else if (flags & FLAG_Q || flags & FLAG_P)
	{
		out = nstrjoin(2, raw_md5(hsh), "\n");
		write(1, out, strlen(out));
	}
	else
	{
		if (flags & FLAG_R)
		{
			raw_md5(hsh);
			out = nstrjoin(4, raw_md5(hsh),
					flags & FLAG_S ? " \"" : " ",
					str,
					flags & FLAG_S ? "\"\n" : "\n");
			write(1, out, strlen(out));
		}
		else
		{
			raw_md5(hsh);
			out = nstrjoin(5,
					flags & FLAG_S ? "MD5 (\"" : "MD5 (",
					str,
					flags & FLAG_S ? "\") = " : ") = ",
					raw_md5(hsh), "\n");
			write(1, out, strlen(out));
		}
	}
}

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

	if (flags & FLAG_S)
	{
		return (fill_buffer_from_str(str, buffer));
	}
	else if (flags & FLAG_P)
	{
		return (fill_buffer_from_stream(0, buffer));
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