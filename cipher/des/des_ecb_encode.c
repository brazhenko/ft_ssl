#include <stdio.h>
#include "des.h"
#include "utilities.h"
#include <string.h>

void 		des_ecb_encode(t_cipher_context *ctx)
{
	DESBLOCK		bl;
	DES64KEY 		key0;
	DES56KEY		key1;
	DES48KEY		key2;
	memcpy(key0, ctx->key, 8);

	while (des_get_block(ctx, &bl))
	{
		// des_ip_forward(&bl);
		des_permutation(bl, bl, des_shfl_tbl, sizeof(des_shfl_tbl) / sizeof(des_shfl_tbl[0]));
		printf("%zu\n", sizeof(des_shfl_tbl) / sizeof(des_shfl_tbl[0]));
		debug64key(&bl);
		des_permutation(key0, key1, init_key_pm, sizeof(init_key_pm) / sizeof(init_key_pm[0]));
		for (int i = 0; i < DES_CIPHER_ROUND_COUNT; ++i)
		{
			rot_des56key_blocks_left_n(&key1, des_key_pd[i]);
			des_permutation(key1, key2, final_key_pm, sizeof(final_key_pm) / sizeof(final_key_pm[0]));
			// operations with block
			des_encode_round(&bl, &key2);
		}
		// Hardcode
		DESHALFBLOCK		tmp;
		memcpy(&tmp, ((uint8_t*)(bl+ 4)), 4);
		memcpy(((uint8_t*)bl + 4), bl, 4);
		memcpy(bl, tmp, 4);
		// ---------

		des_permutation(bl, bl, des_shfl_tbl_r,
				sizeof(des_shfl_tbl_r) / sizeof(des_shfl_tbl_r[0]));
		write(1, bl, 8);
	}
}









