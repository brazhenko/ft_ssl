#include "des.h"
#include <stddef.h>
#include <stdio.h>
#include <utilities.h>

void		*des_ecb(t_cipher_context *ctx)
{
	if (!CPHR_ISKEYSET(ctx))
	{
		if (!CPHR_ISPASSSET(ctx))
			set_cipher_password_from_stdin(ctx);
		if (!CPHR_ISSALTSET(ctx))
			set_cipher_random_pass_salt(ctx, DES_ECB_SALT_BYTE_LEN);
		// generate key
		// pbkdf(); ...
	}
	print_hex_memory(ctx->salt, DES_ECB_SALT_BYTE_LEN);
	if (CPHR_ISENCODEMODE(ctx))
		des_ecb_encode(ctx);
	else if (CPHR_ISDECODEMODE(ctx))
		des_ecb_decode(ctx);
	return (NULL);
}