/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cipher_input_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:32:39 by a17641238         #+#    #+#             */
/*   Updated: 2020/02/03 18:54:38 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <des.h>
#include <unistd.h>
#include <string.h>
#include <utilities.h>
#include <stdio.h>

/*
** des_get_enc_block() returns padded(if needed) block from fd
*/

ssize_t		des_get_enc_block(t_cipher_context *ctx, t_lpdesblock block)
{
	ssize_t				rc;
	static int			end_reading = 0;
	int 				j;

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

static void	wrong_block_size_exit(void)
{
	nstrprinterror(1, "wrong block size, cipher text is corrupted\n");
	exit(EXIT_FAILURE);
}

/*
 * des_get_decr_block() returns 8 if usual block,
 * 1 if last, 0 if no blocks left.
 */

ssize_t		des_get_decr_block(t_cipher_context *ctx, t_lpdesblock block)
{
	ssize_t				rc;
	static int			start = 0;
	static t_desblock	tmp_block;
	static size_t		tmp_size = 0;

	memset(*block, 0, 8);
	if (!start)
	{
		start = 1;
		rc = read(ctx->input_fd, block, 8);
		if (rc == 0)
			return (0);
		else if (rc != 8)
			wrong_block_size_exit();
		tmp_size = read(ctx->input_fd, tmp_block, 8);
		if (tmp_size == 0)
			return (1);
		return (8);
	}
	if (tmp_size == 0)
		return (0);
	else if (tmp_size != 8)
		wrong_block_size_exit();
	memcpy(block, tmp_block, sizeof(tmp_block));
	tmp_size = read(ctx->input_fd, tmp_block, sizeof(tmp_block));
	if (tmp_size == 0)
		return (1);
	return (tmp_size);
}
