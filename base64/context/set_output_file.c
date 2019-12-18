#include "base64.h"
#include <string.h>

int					set_base64_output_file(t_base64_context *ctx,
		const char *output_file_name)
{
	memset(ctx->output_file, '\0', PATH_MAX);
	strcpy(ctx->output_file, output_file_name);
	ctx->mode |= 0b10;
	return (0);
}