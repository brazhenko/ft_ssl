#include "base64.h"

int 				set_base64_encode_mode(t_base64_context *ctx)
{
	ctx->mode &= 0xFFFFFFFE;
	return (0);
}