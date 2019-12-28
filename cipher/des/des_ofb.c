#include "des.h"
#include <stddef.h>
#include <stdio.h>

void		*des_ofb(t_cipher_context *ctx)
{
	if (ISENCODEMODE(ctx))
		des_ofb_encode(ctx);
	else if (ISDECODEMODE(ctx))
		des_ofb_decode(ctx);
	puts("des_ofb() under development");
	return (NULL);
}