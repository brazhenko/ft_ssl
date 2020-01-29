#include "cipher_context.h"
#include <string.h>
#include <unistd.h>

void		destruct_cipher_context(t_cipher_context *ctx)
{
	close(ctx->input_fd);
	close(ctx->output_fd);
	memset(ctx, 0, sizeof(t_cipher_context));
	free(ctx);
}
