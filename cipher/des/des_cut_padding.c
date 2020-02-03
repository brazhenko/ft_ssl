/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cut_padding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:38:23 by a17641238         #+#    #+#             */
/*   Updated: 2020/02/03 18:58:28 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cipher_context.h>
#include <des.h>
#include <string.h>
#include "utilities.h"
#include <stdio.h>

/*
** TODO think of another way to cut padding....
*/

static void	corrupted_last_block_exit(void)
{
	nstrprinterror(1, "last block corrupted...\bexit\n");
}

size_t		des_cut_padding(t_cipher_context *ctx, t_lpdesblock block)
{
	size_t		i;
	
	if (memcmp(((unsigned char *)block) + 7, "\1", 1) == 0)
		(*block)[(i = 7)] = 0;
	else if (memcmp(((unsigned char *)block) + 6, "\2\2", 2) == 0)
		(*block)[(i = 6)] = 0;
	else if (memcmp(((unsigned char *)block) + 5, "\3\3\3", 3) == 0)
		(*block)[(i = 5)] = 0;
	else if (memcmp(((unsigned char *)block) + 4, "\4\4\4\4", 4) == 0)
		(*block)[(i = 4)] = 0;
	else if (memcmp(((unsigned char *)block) + 3, "\5\5\5\5\5", 5) == 0)
		(*block)[(i = 3)] = 0;
	else if (memcmp(((unsigned char *)block) + 2, "\6\6\6\6\6\6", 6) == 0)
		(*block)[(i = 2)] = 0;
	else if (memcmp(((unsigned char *)block) + 1, "\7\7\7\7\7\7\7", 7) == 0)
		(*block)[(i = 1)] = 0;
	else if (memcmp(((unsigned char *)block) + 0,
			"\10\10\10\10\10\10\10\10", 8) == 0)
		(*block)[(i = 0)] = 0;
	else
	{
		i = 8;
		corrupted_last_block_exit();
	}
	return (i);
}
