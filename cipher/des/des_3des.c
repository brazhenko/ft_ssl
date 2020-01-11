#include "des.h"
#include <stddef.h>
#include <stdio.h>

void		*des_3des(t_cipher_context *ctx)
{
	if (CPHR_ISENCODEMODE(ctx))
		;
	else if (CPHR_ISDECODEMODE(ctx))
		;
	puts("des_3des() under development");
	return (NULL);
}