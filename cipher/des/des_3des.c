#include "des.h"
#include <stddef.h>
#include <stdio.h>

void		*des_3des(t_cipher_context *ctx)
{
	if (cphr_is_encrypt_mode(ctx))
		;
	else if (cphr_is_decrypt_mode(ctx))
		;
	puts("des_3des() under development");
	return (NULL);
}