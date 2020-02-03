/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_decrypt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 20:13:13 by a17641238         #+#    #+#             */
/*   Updated: 2020/02/03 17:53:36 by a17641238        ###   ########.fr       */
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
	size_t			cut;

	while ((rd = des_get_decr_block(ctx, &block)))
	{
		des_decrypt_block(ctx->key, &block);
		if (rd == 1)
		{
			cut = des_cut_padding(ctx, &block);
			write(ctx->output_fd, block, cut);
		}
		else
			write(ctx->output_fd, block, sizeof(block));
	}
}
