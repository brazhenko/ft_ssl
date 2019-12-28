#include "des.h"
#include <stddef.h>
#include <stdio.h>

void		*des_cfb(t_cipher_context *ctx)
{
	if (ISENCODEMODE(ctx))
		;
	else if (ISDECODEMODE(ctx))
		;
	puts("des_cfb() under development");
	return (NULL);
}