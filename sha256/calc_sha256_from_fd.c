#include "ft_sha256.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

# define BUFLEN 5120

/*
** 		Returns number of bytes ADDED, NOT the len of all buffer
*/

size_t				calculate_sha256_buf_padding(
		char *padded,
		size_t len
)
{
	size_t		padded_len;
	size_t		ret;

	padded_len = len + 1;
	if (padded_len % 64 < 60)
	{
		ret = 64 - len % 64;
		padded_len = padded_len + (64 - padded_len % 64);
	}
	else
	{
		ret = 64 + (64 - len % 64);
		padded_len = padded_len + 64 + (64 - padded_len % 64);
	}
	// padded_len = padded_len + ((padded_len % 64) ? (64 - padded_len % 64) : 64);

	padded[len % (BUFLEN + 64)] = 0x80;
	padded[(padded_len - 4)  % (BUFLEN + 64)] = ((len * 8) >> 24) & 0b11111111;
	padded[(padded_len - 3)  % (BUFLEN + 64)] = ((len * 8) >> 16) & 0b11111111;
	padded[(padded_len - 2)  % (BUFLEN + 64)] = ((len * 8) >> 8) & 0b11111111;
	padded[(padded_len - 1)  % (BUFLEN + 64)] = ((len * 8) >> 0) & 0b11111111;
	printf("PADDED: %u , a:%u, b:%u\n",
			ret,
			(padded_len - 4)  % (BUFLEN + 64),
			padded_len
	);
	return (ret);
}

static int		get_buffer_from_fd(int fd, char **block)
{
	static char		buffer[BUFLEN + 64];
	static size_t	len = 0;
	static size_t	iter = 0;
	static ssize_t	rd = 0;

	if (iter == rd)
	{
		rd = read(fd, buffer, BUFLEN);
		if (rd == -1)
		{
			printf("Говно, это сраная директория!\n");
			return (-1);
		}
		else if (rd == 0)
		{
			rd = rd + calculate_sha256_buf_padding(buffer, len);
			if (len % BUFLEN == 0)
			{
				// calculate padding
			}
			return (0);
		}
		else
		{
			len += rd;
			iter = 0;
			bzero(buffer, BUFLEN);
		}

	}
	// else
	{

		if (rd - iter < 64)
		{
			rd = rd + calculate_sha256_buf_padding(buffer, len);
		}

		*block = &buffer[iter];
		iter += 64;
	}

	return (1);
}

t_hash_sha256	calculate_sha256_from_file(const char *file_name)
{
	t_hash_sha256	hash;
	ssize_t			fd;
	char			*block_ptr;

	fd = open(file_name, O_RDONLY);
	init_sha256_hash(&hash);

	int i =0;
	while (get_buffer_from_fd(fd, &block_ptr))
	{
		calculate_sha256_block((reg32 *)block_ptr, &hash);

		i++;
		if (i == 10) exit(0);
	}
	return (hash);
}

t_hash_sha256	calculate_sha256_from_stdin(void)
{
	t_hash_sha256	hash;
	char			*block_ptr;

	init_sha256_hash(&hash);
	int i = 0;
	while (get_buffer_from_fd(0, &block_ptr))
	{
		calculate_sha256_block((reg32 *)block_ptr, &hash);

		i++;
		if (i == 10) exit(0);
	}
	return (hash);
}
