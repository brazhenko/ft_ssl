#include "des.h"
#include <string.h>

static void		des_cut_padding(t_cipher_context *ctx, t_lpdesblock block)
{
	// TODO support --nopadding
	if (memcmp(((unsigned char *)block) + 7, "\1", 1) == 0)
		(*block)[7] = 0;
	else if (memcmp(((unsigned char *)block) + 6, "\2\2", 2) == 0)
		(*block)[6] = 0;
	else if (memcmp(((unsigned char *)block) + 5, "\3\3\3", 3) == 0)
		(*block)[5] = 0;
	else if (memcmp(((unsigned char *)block) + 4, "\4\4\4\4", 4) == 0)
		(*block)[4] = 0;
	else if (memcmp(((unsigned char *)block) + 3, "\5\5\5\5\5", 5) == 0)
		(*block)[3] = 0;
	else if (memcmp(((unsigned char *)block) + 2, "\6\6\6\6\6\6", 6) == 0)
		(*block)[2] = 0;
	else if (memcmp(((unsigned char *)block) + 1, "\7\7\7\7\7\7\7", 7) == 0)
		(*block)[1] = 0;
	else if (memcmp(((unsigned char *)block) + 0, "\10\10\10\10\10\10\10\10", 8) == 0)
		(*block)[0] = 0;
}

void 		des_ecb_decrypt(t_cipher_context *ctx)
{
	t_desblock		block;

	while (des_get_decr_block(ctx, &block))
	{
		des_decrypt_block(ctx->key, &block);
		des_cut_padding(ctx, &block);
		write(ctx->output_fd, block, strlen((char *)block) <= 8 ? strlen((char *)block) : 8); //TODO fix
	}
}
