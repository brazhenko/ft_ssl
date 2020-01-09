#include <stdio.h>
#include "des.h"
#include "utilities.h"
#include <string.h>

void 		des_ecb_encode(t_cipher_context *ctx)
{
	DESBLOCK		bl;
	DES56KEY		key1;
	DES48KEY		key2;
	size_t			round;

	while (des_get_block(ctx, &bl))
	{
		// des_ip_forward(&bl);
		des_permutation(bl, bl, des_ip_perm,sizeof(des_ip_perm) / sizeof(des_ip_perm[0]));
		des_permutation(ctx->key, key1, init_key_pm,sizeof(init_key_pm) / sizeof(init_key_pm[0]));

		round = 0;
		while (round < DES_CIPHER_ROUND_COUNT)
		{
			rot_des56key_blocks_left_n(&key1, des_key_pd[round]);
			des_permutation(key1, key2, final_key_pm, sizeof(final_key_pm) / sizeof(final_key_pm[0]));
			// operations with block
			des_encode_round(&bl, &key2);
			round++;
		}

		// Hardcode swapping blocks back
		DESHALFBLOCK		tmp;
		memcpy(&tmp, ((uint8_t*)(bl+ 4)), 4);
		memcpy(((uint8_t*)bl + 4), bl, 4);
		memcpy(bl, tmp, 4);
		// ---------

		des_permutation(bl, bl, des_r_ip_perm,
				sizeof(des_r_ip_perm) / sizeof(des_r_ip_perm[0]));
		printf("%d\n", bl[7]);
		write(1, bl, 8);
	}
}









