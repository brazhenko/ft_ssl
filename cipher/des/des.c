/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:38:10 by a17641238         #+#    #+#             */
/*   Updated: 2020/01/30 17:38:10 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

void		des_encrypt_block(t_des64key key, t_lpdesblock block)
{
	t_des56key		key56;
	t_des48key		final_key;
	size_t			round;

	des_permutation(*block, *block, g_des_ip_perm,
			sizeof(g_des_ip_perm) / sizeof(g_des_ip_perm[0]));
	des_permutation(key, key56, g_init_key_pm,
			sizeof(g_init_key_pm) / sizeof(g_init_key_pm[0]));
	round = 0;
	while (round < DES_CIPHER_ROUND_COUNT)
	{
		rot_des56key_blocks_left_n(&key56, g_des_key_pd[round]);
		des_permutation(key56, final_key, g_final_key_pm,
				sizeof(g_final_key_pm) / sizeof(g_final_key_pm[0]));
		des_round(block, &final_key);
		round++;
	}
	des_swap_block_halves(block);
	des_permutation(*block, *block, g_des_r_ip_perm,
			sizeof(g_des_r_ip_perm) / sizeof(g_des_r_ip_perm[0]));
}

/*
** TODO fix right rotation!
*/

void		des_decrypt_block(t_des64key key, t_lpdesblock block)
{
	t_des56key		key56;
	t_des48key		final_key;
	size_t			round;

	des_permutation(*block, *block, g_des_ip_perm,
			sizeof(g_des_ip_perm) / sizeof(g_des_ip_perm[0]));
	des_permutation(key, key56, g_init_key_pm,
			sizeof(g_init_key_pm) / sizeof(g_init_key_pm[0]));
	round = DES_CIPHER_ROUND_COUNT;
	while (round > 0)
	{
		des_permutation(key56, final_key, g_final_key_pm,
				sizeof(g_final_key_pm) / sizeof(g_final_key_pm[0]));
		des_round(block, &final_key);
		rot_des56key_blocks_left_n(&key56, 28 - g_des_key_pd[round - 1]);
		round--;
	}
	des_swap_block_halves(block);
	des_permutation(*block, *block, g_des_r_ip_perm,
			sizeof(g_des_r_ip_perm) / sizeof(g_des_r_ip_perm[0]));
}
