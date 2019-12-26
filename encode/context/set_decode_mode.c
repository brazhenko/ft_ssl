#include "base64.h"

int 				set_encode_decode_mode(t_encode_context *ctx)
{
	ctx->mode |= 0b1;
	return (0);
}