#include "des.h"
#include <string.h>

/*
** TODO think about normal output
*/

void		des_ecb_decrypt(t_cipher_context *ctx)
{
	t_desblock		block;

	while (des_get_decr_block(ctx, &block))
	{
		des_decrypt_block(ctx->key, &block);
		des_cut_padding(ctx, &block);
		write(ctx->output_fd, block,
		strlen((char *)block) <= 8 ? strlen((char *)block) : 8);
	}
}
