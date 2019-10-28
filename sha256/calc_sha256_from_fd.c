#include "sha256.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

# define BUFLEN 5120

/*
** 		Returns number of bytes ADDED, NOT the len of all buffer
*/

static size_t	calculate_sha256_buf_padding(char *padded, size_t len)
{
	size_t		padded_len;
	size_t		ret;

	padded_len = len + 1;
	ret = 0;
	padded[len % (BUFLEN)] = 0x80;
	if ((padded_len % 64 == 0) || (padded_len % 64 >= 60))
	{
		ret = 64 + (64 - len % 64);
		padded_len = ret + len;
	}
	else
	{
		ret = 64 - len % 64;
		padded_len = ret + len;
	}
	padded[(padded_len - 4)  % (BUFLEN)] = ((len * 8) >> 24) & 0b11111111;
	padded[(padded_len - 3)  % (BUFLEN)] = ((len * 8) >> 16) & 0b11111111;
	padded[(padded_len - 2)  % (BUFLEN)] = ((len * 8) >> 8) & 0b11111111;
	padded[(padded_len - 1)  % (BUFLEN)] = ((len * 8) >> 0) & 0b11111111;
	// printf("calc_padding() ret: %lu padded_len: %lu len: %lu\n", ret, padded_len, len);
	return (ret);
}

static int		get_block_from_fd(int fd, char **block)
{
	static char		buffer[BUFLEN + 64];
	static size_t	iter = 0;
	static size_t	len = 0;
	static ssize_t	rd = 0;
	static int		padded = 0;

	if (iter == rd)
	{
		bzero(buffer, BUFLEN + 64);
		if ((rd = read(fd, buffer, BUFLEN)) == -1)
			return (-1);
		len += rd;
		iter = 0;
		if (rd == 0 && padded == 1)
		{
			bzero(buffer, BUFLEN + 64);
			iter = 0;
			len = 0;
			rd = 0;
			padded = 0;
            return (0);
		}
		if (rd < BUFLEN)
		{
			rd += calculate_sha256_buf_padding(buffer, len);
			padded = 1;
		}
	}
	if (iter < rd)
	{
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
	int				ret;

	init_sha256_hash(&hash);
	fd = open(file_name, O_RDONLY);

	int i = 0;
	while ((ret = get_block_from_fd(fd, &block_ptr)))
	{
		if (ret == -1)
		{
			hash.error = 1;
			return (hash);
		}
		calculate_sha256_block((reg32 *)block_ptr, &hash);
		i++;
		if (i == 1000000)
		{
			printf("exit()\n");
			exit(0);
		}
	}
	return (hash);
}

// TODO fix it
t_hash_sha256	calculate_sha256_from_stdin(void)
{
	t_hash_sha256	hash;
	char			*block_ptr;

	init_sha256_hash(&hash);
	int i = 0;
	while (get_block_from_fd(0, &block_ptr))
	{
		calculate_sha256_block((reg32 *)block_ptr, &hash);

		i++;
		if (i == 100000)
        {
		    printf("exit()");
            exit(0);
        }
	}
	return (hash);
}
