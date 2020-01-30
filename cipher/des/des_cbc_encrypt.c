/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc_encrypt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:38:19 by a17641238         #+#    #+#             */
/*   Updated: 2020/01/30 17:38:19 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cipher_context.h>
#include <des.h>
#include "utilities.h"
#include "string.h"

void		des_cbc_encrypt(t_cipher_context *ctx)
{
	t_desblock		block;

	while (des_get_enc_block(ctx, &block))
	{
		mem_xor(&block, ctx->vector_ini, &block, DES_CIPHER_BLOCK_LEN);
		des_encrypt_block(ctx->key, &block);
		memcpy(ctx->vector_ini, block, DES_CIPHER_BLOCK_LEN);
		write(ctx->output_fd, block, sizeof(block));
	}
}
