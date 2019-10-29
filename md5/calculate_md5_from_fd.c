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

#define BUFLEN 10240

/*
** 		Returns number of bytes ADDED, NOT the len of all buffer
*/

static size_t	calculate_md5_buf_padding(char *padded, size_t len)
{
	size_t		pd_len;
	size_t		ret;
	size_t		lst_b;

	pd_len = len + 1;
	ret = 0;
	padded[len % (BUFLEN)] = 0x80;
	if ((pd_len % 64 == 0) || (pd_len % 64 > 56))
		ret = 64 + (64 - len % 64);
	else
		ret = 64 - len % 64;
	pd_len = ret + len;
	if (BUFLEN - 8 <= len % (BUFLEN) && len % (BUFLEN) < BUFLEN)
		lst_b = pd_len % (BUFLEN + 64) ? pd_len % (BUFLEN + 64) : (BUFLEN + 64);
	else
		lst_b = pd_len % (BUFLEN) ? pd_len % (BUFLEN) : BUFLEN;
	padded[lst_b - 8] = (len * 8) >> (8 * 0) & A;
	padded[lst_b - 7] = (len * 8) >> (8 * 1) & A;
	padded[lst_b - 6] = (len * 8) >> (8 * 2) & A;
	padded[lst_b - 5] = (len * 8) >> (8 * 3) & A;
	padded[lst_b - 4] = (len * 8) >> (8 * 4) & A;
	padded[lst_b - 3] = (len * 8) >> (8 * 5) & A;
	padded[lst_b - 2] = (len * 8) >> (8 * 6) & A;
	padded[lst_b - 1] = (len * 8) >> (8 * 7) & A;
	return (ret);
}

static int		reset_get_block_from_fd(size_t *iter, size_t *len,
										ssize_t *rd, int *padded)
{
	*iter = 0;
	*len = 0;
	*rd = 0;
	*padded = 0;
	return (0);
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
			return (reset_get_block_from_fd(&iter, &len, &rd, &padded));
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

t_hash_md5		calculate_md5_from_file(const char *file_name)
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
		calculate_md5_block((t_reg32 *)block_ptr, &hash);
	}
	return (hash);
}

t_hash_md5		calculate_md5_from_stdin(int flag_p)
{
	t_hash_md5		hash;
	char			*block_ptr;

	init_md5_hash(&hash);
	while (get_block_from_fd(0, &block_ptr, flag_p & FLAG_P))
	{
		calculate_md5_block((t_reg32 *)block_ptr, &hash);
	}
	return (hash);
}
