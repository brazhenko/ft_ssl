#include "des.h"
#include <stddef.h>
#include <stdio.h>

void		*des_cbc(t_cipher_context *ctx)
{
	if (ISENCODEMODE(ctx))
		;
	else if (ISDECODEMODE(ctx))
		;
	puts("des_cbc() under development");
	return (NULL);
}