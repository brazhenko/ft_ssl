#include <cipher_context.h>
#include <des.h>
#include <utilities.h>
#include "string.h"

/*
** TODO improve output
*/

void 		des_cbc_decrypt(t_cipher_context *ctx)
{
	t_desblock		block;
	t_desblock		tmp;

	while (des_get_decr_block(ctx, &block))
	{
		memcpy(tmp, block, DES_CIPHER_BLOCK_LEN);
		des_decrypt_block(ctx->key, &tmp);
		mem_xor(&tmp, ctx->vector_ini, &tmp, DES_CIPHER_BLOCK_LEN);
		memcpy(ctx->vector_ini, block, DES_CIPHER_BLOCK_LEN);
		des_cut_padding(ctx, &tmp);
		write(ctx->output_fd, tmp,
		strlen((char *)tmp) <= 8 ? strlen((char *)tmp) : 8);
	}
}
