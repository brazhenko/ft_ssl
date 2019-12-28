#include "des.h"
#include <stddef.h>
#include <stdio.h>

void		*des_ctr(t_cipher_context *ctx)
{
	if (ISENCODEMODE(ctx))
		;
	else if (ISDECODEMODE(ctx))
		;
	puts("des_ctr() under development");
	return (NULL);
}