/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_encrypt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:34:12 by a17641238         #+#    #+#             */
/*   Updated: 2020/02/03 11:34:12 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

void			des_ecb_encrypt(t_cipher_context *ctx)
{
	t_desblock		block;

	while (des_get_enc_block(ctx, &block))
	{
		des_encrypt_block(ctx->key, &block);
		write(ctx->output_fd, block, sizeof(block));
	}
}
