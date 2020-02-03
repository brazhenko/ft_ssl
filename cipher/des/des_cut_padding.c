/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cut_padding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:38:23 by a17641238         #+#    #+#             */
/*   Updated: 2020/02/03 19:16:28 by lreznak-         ###   ########.fr       */
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
	exit(EXIT_FAILURE);
}

size_t		des_cut_padding(t_cipher_context *ctx, t_lpdesblock block)
{
	if (memcmp(((unsigned char *)block) + 7, "\1", 1) == 0)
		return (7);
	else if (memcmp(((unsigned char *)block) + 6, "\2\2", 2) == 0)
		return (6);
	else if (memcmp(((unsigned char *)block) + 5, "\3\3\3", 3) == 0)
		return (5);
	else if (memcmp(((unsigned char *)block) + 4, "\4\4\4\4", 4) == 0)
		return (4);
	else if (memcmp(((unsigned char *)block) + 3, "\5\5\5\5\5", 5) == 0)
		return (3);
	else if (memcmp(((unsigned char *)block) + 2, "\6\6\6\6\6\6", 6) == 0)
		return (2);
	else if (memcmp(((unsigned char *)block) + 1, "\7\7\7\7\7\7\7", 7) == 0)
		return (1);
	else if (memcmp(((unsigned char *)block) + 0,
			"\10\10\10\10\10\10\10\10", 8) == 0)
		return (0);
	else
		corrupted_last_block_exit();
	return (0);
}
