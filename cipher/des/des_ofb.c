#include "des.h"
#include <stddef.h>
#include <stdio.h>

void		*des_ofb(t_cipher_context *ctx)
{
	if (CPHR_ISENCRYPTMODE(ctx))
		des_ofb_encode(ctx);
	else if (CPHR_ISDECRYPTMODE(ctx))
		des_ofb_decode(ctx);
	puts("des_ofb() under development");
	return (NULL);
}