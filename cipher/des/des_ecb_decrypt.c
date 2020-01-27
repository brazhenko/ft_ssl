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

void		des_decrypt_block(t_des64key key, t_lpdesblock block)
{
	t_des56key		key56;
	t_des48key		final_key;
	size_t			round;

	des_permutation(*block, *block, des_ip_perm,
	sizeof(des_ip_perm) / sizeof(des_ip_perm[0]));
	des_permutation(key, key56, init_key_pm,
	sizeof(init_key_pm) / sizeof(init_key_pm[0]));
	round = DES_CIPHER_ROUND_COUNT;
	while (round > 0)
	{
		// TODO fix right rotation!
		des_permutation(key56, final_key, final_key_pm,
		sizeof(final_key_pm) / sizeof(final_key_pm[0]));
		des_round(block, &final_key);
		rot_des56key_blocks_left_n(&key56, 28-des_key_pd[round - 1]);
		round--;
	}
	des_swap_block_halves(block);
	des_permutation(*block, *block, des_r_ip_perm,
	sizeof(des_r_ip_perm) / sizeof(des_r_ip_perm[0]));
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
