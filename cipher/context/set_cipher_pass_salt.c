/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cipher_pass_salt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:37:48 by a17641238         #+#    #+#             */
/*   Updated: 2020/01/30 17:37:48 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher_context.h"
#include <string.h>
#include <utilities.h>

static const uint8_t	g_hex2bin[] =
{
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u,
	8, 9, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 10u, 11u, 12u, 13u, 14u, 15u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 10u, 11u, 12u, 13u, 14u, 15u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
};

static void		cipher_hex_salt_too_long_exit(void)
{
	nstrprinterror(1, "hex string is too long\n");
	exit(EXIT_FAILURE);
}

static void		cipher_salt_non_hex_exit(void)
{
	nstrprinterror(1, "non-hex digit\n");
	exit(EXIT_FAILURE);
}

/*
** Translates hex salt [char *arg] to binary and puts it to ctx->salt.
*/

void			set_cipher_pass_salt(t_cipher_context *ctx, char *arg)
{
	size_t		i;
	uint8_t		bin;

	memset(ctx->salt, 0, CIPHER_SALT_BYTE_LEN);
	ctx->mode |= 0b1000000;
	i = 0;
	while (arg[i])
	{
		if (i == CIPHER_SALT_BYTE_LEN * 2)
			cipher_hex_salt_too_long_exit();
		bin = g_hex2bin[(uint8_t)arg[i]];
		if (bin || arg[i] == '0')
		{
			ctx->salt[i / 2] |= (bin << (4u * (1u - i % 2u)));
		}
		else
			cipher_salt_non_hex_exit();
		i++;
	}
}
