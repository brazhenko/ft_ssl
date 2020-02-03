/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_decrypt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 20:13:13 by a17641238         #+#    #+#             */
/*   Updated: 2020/02/03 17:21:01 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include <string.h>
#include <stdio.h>

/*
** TODO think about normal output
*/

void		des_ecb_decrypt(t_cipher_context *ctx)
{
	t_desblock		block;
	ssize_t			rd;

	while ((rd = des_get_decr_block(ctx, &block)))
	{
		des_decrypt_block(ctx->key, &block);
		if (rd == 1)
			des_cut_padding(ctx, &block);
		write(ctx->output_fd, block,
		strnlen((char *)block, 8) <= 8 ? strnlen((char *)block, 8) : 8);
	}
}
