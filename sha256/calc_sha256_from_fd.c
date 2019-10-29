/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sha256_from_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:10:45 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/28 23:10:46 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFLEN 5120

/*
** 		Returns number of bytes ADDED, NOT the len of all buffer
*/

static size_t	calculate_sha256_buf_padding(char *padded, size_t len)
{
	size_t		padded_len;
	size_t		ret;
	size_t		last_byte_num;

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
	if (BUFLEN - 9 <= len % (BUFLEN) && len % (BUFLEN) < BUFLEN)
	{
		last_byte_num = padded_len % (BUFLEN + 64) ? padded_len % (BUFLEN + 64) : (BUFLEN + 64);
	}
	else
	{
		last_byte_num = padded_len % (BUFLEN) ? padded_len % (BUFLEN) : BUFLEN;
	}
	padded[last_byte_num - 4] = ((len * 8) >> 24) & 0b11111111;
	padded[last_byte_num - 3] = ((len * 8) >> 16) & 0b11111111;
	padded[last_byte_num - 2] = ((len * 8) >> 8) & 0b11111111;
	padded[last_byte_num - 1] = ((len * 8) >> 0) & 0b11111111;
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
		if (flag_p)
			write(1, buffer, rd);
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
		calculate_sha256_block((t_reg32 *)block_ptr, &hash);
	}
	return (hash);
}

t_hash_sha256	calculate_sha256_from_stdin(int flag_p)
{
	t_hash_sha256	hash;
	char			*block_ptr;

	init_sha256_hash(&hash);
	while (get_block_from_fd(0, &block_ptr, flag_p))
	{
		calculate_sha256_block((t_reg32 *)block_ptr, &hash);
	}
	return (hash);
}
