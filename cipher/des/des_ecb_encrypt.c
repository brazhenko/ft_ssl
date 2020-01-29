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
