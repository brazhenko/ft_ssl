#include "des.h"
#include <string.h>

void 		des_ecb_encrypt(t_cipher_context *ctx)
{

	t_desblock		block;
	t_des56key		key56;
	t_des48key		final_key;
	size_t			round;

	while (des_get_enc_block(ctx, &block))
	{
		des_permutation(block, block, des_ip_perm,
		sizeof(des_ip_perm) / sizeof(des_ip_perm[0]));
		des_permutation(ctx->key, key56, init_key_pm,
		sizeof(init_key_pm) / sizeof(init_key_pm[0]));
		round = 0;
		while (round < DES_CIPHER_ROUND_COUNT)
		{
			rot_des56key_blocks_left_n(&key56, des_key_pd[round]);
			des_permutation(key56, final_key, final_key_pm,
			sizeof(final_key_pm) / sizeof(final_key_pm[0]));

			des_round(&block, &final_key);
			round++;
		}
		des_swap_block_halves(&block);
		des_permutation(block, block, des_r_ip_perm,
		sizeof(des_r_ip_perm) / sizeof(des_r_ip_perm[0]));
		write(ctx->output_fd, block, sizeof(block));
	}
}









