#include "cipher_context.h"

int		set_cipher_bufsize(t_cipher_context *ctx, const char *argv)
{
	ctx->bufsize = atoi(argv);
	return (0);
}