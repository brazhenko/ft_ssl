#include "base64.h"

int 				set_base64_decode_mode(t_base64_context *ctx)
{
	ctx->mode |= 0b1;
	return (0);
}