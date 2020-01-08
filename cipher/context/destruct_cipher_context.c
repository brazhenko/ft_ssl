#include "cipher_context.h"
#include <string.h>

void		destruct_cipher_context(t_cipher_context *ctx)
{
	memset(ctx, 0, sizeof(t_cipher_context));
	free(ctx);
}