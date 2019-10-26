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
	if (len % 64 < 60)
	{
		ret = 64 - len % 64;
		padded_len = padded_len + (64 - padded_len % 64);
	}
	else
	{
		ret = 64 + (64 - len % 64);
		padded_len = padded_len + 64 + (64 - padded_len % 64);
	}

	padded[len % (BUFLEN + 64)] = 0x80;
	padded[(padded_len - 4)  % (BUFLEN + 64)] = ((len * 8) >> 24) & 0b11111111;
	padded[(padded_len - 3)  % (BUFLEN + 64)] = ((len * 8) >> 16) & 0b11111111;
	padded[(padded_len - 2)  % (BUFLEN + 64)] = ((len * 8) >> 8) & 0b11111111;
	padded[(padded_len - 1)  % (BUFLEN + 64)] = ((len * 8) >> 0) & 0b11111111;
	printf("PADDED: %u , a:%u, b:%u len: %u\n",
			ret,
			(padded_len - 4)  % (BUFLEN + 64),
			padded_len,
			len
	);
	print_bit_str("abc: ", padded, 128);
	return (ret);
}

static int		get_block_from_fd(int fd, char **block)
{
	static char		buffer[BUFLEN + 64];
	static size_t	len = 0;
	static size_t	iter = 0;
	static ssize_t	rd = 0;
	int				padd1 = 0;

	if (!rd)
	{
		bzero(buffer, BUFLEN);
		rd = read(fd, buffer, BUFLEN);
		len += rd;
		if (!fd)
			; // padding
			// TODO extra shedules
	}
	while (rd >= 64)
	{
		*block = buffer[BUFLEN - rd];
		rd -= 64;
		return (1);
	}


	return (1);
}

t_hash_sha256	calculate_sha256_from_file(const char *file_name)
{
	t_hash_sha256	hash;
	ssize_t			fd;
	char			*block_ptr;
	int				ret;

	fd = open(file_name, O_RDONLY);
	init_sha256_hash(&hash);

	int i = 0;
	while ((ret = get_block_from_fd(fd, &block_ptr)))
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
	while (get_block_from_fd(0, &block_ptr))
	{
		calculate_sha256_block((reg32 *)block_ptr, &hash);

		i++;
		if (i == 10) exit(0);
	}
	return (hash);
}
