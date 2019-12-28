#include <stdio.h>
#include "des.h"
#include "utilities.h"

void 		des_ecb_encode(t_cipher_context *ctx)
{
	DESBLOCK	bl;
	puts("DEBUG: des_ecb_encode()");
	while (des_get_block(ctx, &bl))
	{
		des_ip_debug(&bl);
		des_ip_forward(&bl);
		des_ip_debug(&bl);

		des_ip_reverse(&bl);
		des_ip_debug(&bl);
	}
}

