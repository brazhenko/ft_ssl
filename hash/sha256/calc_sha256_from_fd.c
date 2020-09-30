/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sha256_from_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:10:45 by lreznak-          #+#    #+#             */
/*   Updated: 2020/09/30 15:05:05 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

/*
** 		Returns number of bytes ADDED, NOT the len of all buffer
** 		lst_b - the "last" byte after padding where no vital data will
** 		be stored (inside the buffer[BUFFLEN + 64])
**		pd_len - padded len, total len of stream.
*/

static int		reset_get_block_from_fd(size_t *iter, size_t *len,
		ssize_t *rd, int *padded)
{
	*iter = 0;
	*len = 0;
	*rd = 0;
	*padded = 0;
	return (0);
}

static void		move_iter(char **ret_block,
				char *buffer, size_t *iter, ssize_t rd)
{
	if ((ssize_t)*iter < rd)
	{
		*ret_block = &buffer[*iter];
		*iter = *iter + 64;
	}
}

static int		get_block_from_fd(int fd, char **block, int flag_p)
{
	static char		buffer[BUFLEN + 64];
	static ssize_t	it = 0;
	static size_t	len = 0;
	static ssize_t	rd = 0;
	static int		padded = 0;

	if (it == rd)
	{
		bzero(buffer, BUFLEN + 64);
		if ((rd = read(fd, buffer, BUFLEN)) == -1)
			return (-1);
		if (flag_p)
			write(1, buffer, rd);
		len += rd;
		it = 0;
		if (rd == 0 && padded == 1)
			return (reset_get_block_from_fd((size_t*)&it, &len, &rd, &padded));
		if (rd < BUFLEN)
		{
			rd += calculate_sha256_buf_padding(buffer, len);
			padded = 1;
		}
	}
	move_iter(block, (char *)&buffer, (size_t*)&it, rd);
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
