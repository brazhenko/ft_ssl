/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cipher_input_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:32:39 by a17641238         #+#    #+#             */
/*   Updated: 2020/02/03 11:53:29 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <des.h>
#include <unistd.h>
#include <string.h>
#include <utilities.h>

/*
** des_get_enc_block() returns padded(if needed) block from fd
*/

ssize_t		des_get_enc_block(t_cipher_context *ctx, t_lpdesblock block)
{
	ssize_t			rc;
	static int		end_reading = 0;
	int 			j;

	if (end_reading)
		return (0);
	memset(*block, 0, DES_CIPHER_BLOCK_LEN);
	rc = read(ctx->input_fd, block, DES_CIPHER_BLOCK_LEN);
	if (rc != 8)
	{
		j = rc;
		while (j < 8)
		{
			(*block)[j] = 8 - rc;
			j++;
		}
		end_reading = 1;
	}
	return (1);
}

ssize_t		des_get_decr_block(t_cipher_context *ctx, t_lpdesblock block)
{
	ssize_t		rc;

	memset(*block, 0, 8);
	rc = read(ctx->input_fd, block, 8);
	if (rc == 0)
		return (rc);
	if (rc != 8)
	{
		nstrprinterror(1, "wrong block size, cipher text is corrupted\n");
		exit(EXIT_FAILURE);
	}
	return (rc);
}
