/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc_decrypt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:33:58 by a17641238         #+#    #+#             */
/*   Updated: 2020/02/03 17:20:49 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cipher_context.h>
#include <des.h>
#include <utilities.h>
#include "string.h"
#include <stdio.h>

/*
** TODO improve output
*/

void			des_cbc_decrypt(t_cipher_context *ctx)
{
	t_desblock		block;
	t_desblock		tmp;
	ssize_t			rd;

	while ((rd = des_get_decr_block(ctx, &block)))
	{
		memcpy(tmp, block, DES_CIPHER_BLOCK_LEN);
		des_decrypt_block(ctx->key, &tmp);
		mem_xor(&tmp, ctx->vector_ini, &tmp, DES_CIPHER_BLOCK_LEN);
		memcpy(ctx->vector_ini, block, DES_CIPHER_BLOCK_LEN);
		if (rd == 1)
		{
			des_cut_padding(ctx, &block);
			write(ctx->output_fd, block,strnlen((char *)block, 8));
		}
		else
			write(ctx->output_fd, block,8);
	}
}
