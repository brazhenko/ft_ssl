/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_md5_from_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:17:34 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/28 23:17:35 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

#include "md5.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFLEN 5120

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
	if ((padded_len % 64 == 0) || (padded_len % 64 > 56))
	{
		ret = 64 + (64 - len % 64);
		padded_len = ret + len;
	}
	else
	{
		ret = 64 - len % 64;
		padded_len = ret + len;
	}
	// printf("pl: %lu\n", padded_len);
	padded[(padded_len - 8) % (BUFLEN + 64)] = (len * 8) >> (8 * 0) & A;
	padded[(padded_len - 7) % (BUFLEN + 64)] = (len * 8) >> (8 * 1) & A;
	padded[(padded_len - 6) % (BUFLEN + 64)] = (len * 8) >> (8 * 2) & A;
	padded[(padded_len - 5) % (BUFLEN + 64)] = (len * 8) >> (8 * 3) & A;
	padded[(padded_len - 4) % (BUFLEN + 64)] = (len * 8) >> (8 * 4) & A;
	padded[(padded_len - 3) % (BUFLEN + 64)] = (len * 8) >> (8 * 5) & A;
	padded[(padded_len - 2) % (BUFLEN + 64)] = (len * 8) >> (8 * 6) & A;
	padded[(padded_len - 1) % (BUFLEN + 64)] = (len * 8) >> (8 * 7) & A;
	// print_bit_str("deb1 ", padded, 64);
	// print_bit_str("kekch: ", padded, 64);
//	print_bit_str("kekch2: ", padded+5120, 64);

	return (ret);
}

static int		get_block_from_fd(int fd, char **block, int flag_p)
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
		// print_bit_str("com2 ", buffer, rd);
		if (flag_p)
			write(1, buffer, rd);
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
		// printf("rd: %lu, padded: %d\n", rd, padded);
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
	t_hash_md5		hash;
	ssize_t			fd;
	char			*block_ptr;
	int				ret;

	init_md5_hash(&hash);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		hash.error = 2;
		return (hash);
	}
	while ((ret = get_block_from_fd(fd, &block_ptr, 0)))
	{
		if (ret == -1)
		{
			hash.error = 1;
			return (hash);
		}
		calculate_md5_block((reg32 *)block_ptr, &hash);
	}
	return (hash);
}

t_hash_md5	calculate_md5_from_stdin(int flag_p)
{
	t_hash_md5		hash;
	char			*block_ptr;

	init_md5_hash(&hash);
	while (get_block_from_fd(0, &block_ptr, flag_p & FLAG_P))
	{
		calculate_md5_block((reg32 *)block_ptr, &hash);
	}
	return (hash);
}
