#include "des.h"
#include "utilities.h"
#include <string.h>
#include <unistd.h>

t_des_context	*init_des_context(void)
{
	t_des_context	*ctx;

	ctx = (t_des_context *)xmalloc(sizeof(t_des_context));
	memset(ctx, 0, sizeof(t_des_context));
	ctx->output_fd = STDOUT_FILENO;
	ctx->input_fd = STDIN_FILENO;
	return (ctx);
}