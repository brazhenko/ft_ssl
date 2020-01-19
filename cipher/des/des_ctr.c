#include "des.h"
#include <stddef.h>
#include <stdio.h>

void		*des_ctr(t_cipher_context *ctx)
{
	if (CPHR_ISENCRYPTMODE(ctx))
		;
	else if (CPHR_ISDECRYPTMODE(ctx))
		;
	puts("des_ctr() under development");
	return (NULL);
}