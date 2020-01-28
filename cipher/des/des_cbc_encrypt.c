#include <cipher_context.h>
#include <des.h>
#include "utilities.h"
#include "string.h"

void 		des_cbc_encrypt(t_cipher_context *ctx)
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
