#include <stdio.h>
#include "des.h"
#include "utilities.h"
#include <string.h>

void 		des_ecb_encode(t_cipher_context *ctx)
{
	DESBLOCK		bl;
	DESHALFBLOCK 	left;
	DESHALFBLOCK	right;
	DES64KEY 		key0;
	DES56KEY		key1;
	DES48KEY		key2;
	memcpy(key0, "64bitKey", 8);

	puts("DEBUG: des_ecb_encode()");
	while (des_get_block(ctx, &bl))
	{
		des_ip_forward(&bl);

		des_ip_debug(&key0);
		des_permute_key1(&key0);
		des_ip_debug(&key0);
//00110110 00110100 01100010 01101001 01110100 01001011 01100101 01111001
//00110110 00110100 01100010 01101001 01110100 01001011 01100101 01111001

//00000000 11111100 11011111 10010000 00100101 01010011 10101000 00110000
//00000000 11111100 11011111 10010010 01010101 00111010 10000011 00001000


		des_ip_reverse(&bl);
	}
}

