#include "ssl.h"

#include "md5.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

# define BUFLEN 5120

/*
** 		Returns number of bytes ADDED, NOT the len of all buffer
*/

static size_t	calculate_md5_buf_padding(char *padded, size_t len)
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
	padded[(padded_len - 8)  % (BUFLEN)] = (len * 8) >> (8 * 0) & A;
	padded[(padded_len - 7)  % (BUFLEN)] = (len * 8) >> (8 * 1) & A;
	padded[(padded_len - 6)  % (BUFLEN)] = (len * 8) >> (8 * 2) & A;
	padded[(padded_len - 5)  % (BUFLEN)] = (len * 8) >> (8 * 3) & A;
	padded[(padded_len - 4)  % (BUFLEN)] = (len * 8) >> (8 * 4) & A;
	padded[(padded_len - 3)  % (BUFLEN)] = (len * 8) >> (8 * 5) & A;
	padded[(padded_len - 2)  % (BUFLEN)] = (len * 8) >> (8 * 6) & A;
	padded[(padded_len - 1)  % (BUFLEN)] = (len * 8) >> (8 * 7) & A;
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
		// printf("rd: %lu, padded: %d\n", rd, padded);
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
			rd += calculate_md5_buf_padding(buffer, len);
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

t_hash_md5	calculate_md5_from_file(const char *file_name)
{
	t_hash_md5	hash;
	ssize_t			fd;
	char			*block_ptr;
	int				ret;

	init_md5_hash(&hash);
	fd = open(file_name, O_RDONLY);

	int i = 0;
	while ((ret = get_block_from_fd(fd, &block_ptr)))
	{
		if (ret == -1)
		{
			hash.error = 1;
			return (hash);
		}
		calculate_md5_block((reg32 *)block_ptr, &hash);
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
t_hash_md5	calculate_md5_from_stdin(void)
{
	t_hash_md5	hash;
	char			*block_ptr;

	init_md5_hash(&hash);
	int i = 0;
	while (get_block_from_fd(0, &block_ptr))
	{
		printf("deb1\n");

		calculate_md5_block((reg32 *)block_ptr, &hash);
		printf("deb2\n");
		i++;
		if (i == 100000) exit(0);
	}
	return (hash);
}
