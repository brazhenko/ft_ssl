#include "des.h"
#include <stddef.h>
#include <stdio.h>

void		*des_3des(t_cipher_context *ctx)
{
	if (ISENCODEMODE(ctx))
		;
	else if (ISDECODEMODE(ctx))
		;
	puts("des_3des() under development");
	return (NULL);
}