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
	memcpy(key0, "64bitKey", 8);

	puts("DEBUG: des_ecb_encode()");
	while (des_get_block(ctx, &bl))
	{
		des_ip_forward(&bl);

		des_init_key_permutation(&key0, &key1);
		for (int i = 0; i < DES_CIPHER_ROUND_COUNT; ++i)
		{
			rot_des56key_blocks_left_n(&key1, des_key_pd[i]);
			des_final_key_permutation(&key1, &key2);
			// operations with block

		}
		des_ip_reverse(&bl);
	}
}

