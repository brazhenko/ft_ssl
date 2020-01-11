#include "des.h"
#include <stddef.h>
#include <stdio.h>

void		*des_cfb(t_cipher_context *ctx)
{
	if (CPHR_ISENCODEMODE(ctx))
		;
	else if (CPHR_ISDECODEMODE(ctx))
		;
	puts("des_cfb() under development");
	return (NULL);
}