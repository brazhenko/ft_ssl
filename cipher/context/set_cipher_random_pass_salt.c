/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cipher_random_pass_salt.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:32:30 by a17641238         #+#    #+#             */
/*   Updated: 2020/01/30 17:32:30 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher_context.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "utilities.h"

/*
** Reads from /dev/urandom some random data and puts it to [ctx]->salt.
** [size_t byte_len] must be not more that sizeof(ctx->salt).
*/

int		set_cipher_random_pass_salt(t_cipher_context *ctx, size_t byte_len)
{
	int			fd;

	fd = open("/dev/urandom", O_RDONLY);
	memset(ctx->salt, 0, sizeof(ctx->salt));
	if (fd < 0)
	{
		perror("Cannot open /dev/urandom: ");
		exit(EXIT_FAILURE);
	}
	read(fd, ctx->salt, byte_len);
	ctx->mode |= 0b1000000;
	return (0);
}
