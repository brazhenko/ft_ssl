#include "des.h"
#include <stddef.h>

void		*des_ecb(t_cipher_context *ctx)
{
	if (ISENCODEMODE(ctx))
		des_ecb_encode(ctx);
	else if (ISDECODEMODE(ctx))
		des_ecb_decode(ctx);
	return (NULL);
}