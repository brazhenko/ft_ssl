#include "des.h"
#include <stddef.h>
#include <stdio.h>

void		*des_cbc(t_cipher_context *ctx)
{
	if (cphr_is_encrypt_mode(ctx))
		;
	else if (cphr_is_decrypt_mode(ctx))
		;
	puts("des_cbc() under development");
	return (NULL);
}