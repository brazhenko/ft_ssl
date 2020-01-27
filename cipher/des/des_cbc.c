#include "des.h"
#include <stddef.h>
#include <stdio.h>
#include <md5.h>

void		*des_cbc(t_cipher_context *ctx)
{

	if (cphr_is_encrypt_mode(ctx))
		;
	else if (cphr_is_decrypt_mode(ctx))
		;


	puts("des_cbc()");
	puts("IV");
	print_hex_memory(ctx->vector_ini, 8);
	puts("KEY");
	print_hex_memory(ctx->key, 8);
	puts("SALT");
	print_hex_memory(ctx->salt, 8);
	return (NULL);
}