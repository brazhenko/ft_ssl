#include "des.h"
#include "utilities.h"
#include <string.h>
#include <unistd.h>

t_cipher_context	*init_des_context(void)
{
	t_cipher_context	*ctx;

	ctx = (t_cipher_context *)xmalloc(sizeof(t_cipher_context));
	memset(ctx, 0, sizeof(t_cipher_context));
	ctx->output_fd = STDOUT_FILENO;
	ctx->input_fd = STDIN_FILENO;
	return (ctx);
}