#include "base64.h"
#include <string.h>

int					set_base64_input_file(t_base64_context *ctx,
							const char *input_file_name)
{
	memset(ctx->input_file, '\0', PATH_MAX);
	strcpy(ctx->input_file, input_file_name);
	ctx->mode |= 0b100;
	return (0);
}