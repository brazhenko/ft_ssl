#include "des.h"
#include <stddef.h>
#include <stdio.h>

void		*des_cbc(t_cipher_context *ctx)
{
	if (CPHR_ISENCODEMODE(ctx))
		;
	else if (CPHR_ISDECODEMODE(ctx))
		;
	puts("des_cbc() under development");
	return (NULL);
}