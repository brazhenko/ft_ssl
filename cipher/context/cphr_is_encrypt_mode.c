#include "cipher_context.h"

int 		cphr_is_encrypt_mode(t_cipher_context *ctx)
{
	return (!(ctx->mode & 0b1U));
}