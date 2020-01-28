#include "des.h"

void		des_encrypt_block(t_des64key key, t_lpdesblock block)
{
	t_des56key		key56;
	t_des48key		final_key;
	size_t			round;

	des_permutation(*block, *block, g_des_ip_perm,
			sizeof(g_des_ip_perm) / sizeof(g_des_ip_perm[0]));
	des_permutation(key, key56, init_key_pm,
			sizeof(init_key_pm) / sizeof(init_key_pm[0]));
	round = 0;
	while (round < DES_CIPHER_ROUND_COUNT)
	{
		rot_des56key_blocks_left_n(&key56, des_key_pd[round]);
		des_permutation(key56, final_key, final_key_pm,
				sizeof(final_key_pm) / sizeof(final_key_pm[0]));
		des_round(block, &final_key);
		round++;
	}
	des_swap_block_halves(block);
	des_permutation(*block, *block, des_r_ip_perm,
			sizeof(des_r_ip_perm) / sizeof(des_r_ip_perm[0]));
}

void		des_decrypt_block(t_des64key key, t_lpdesblock block)
{
	t_des56key		key56;
	t_des48key		final_key;
	size_t			round;

	des_permutation(*block, *block, g_des_ip_perm,
			sizeof(g_des_ip_perm) / sizeof(g_des_ip_perm[0]));
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