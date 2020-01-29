#include "base64.h"

int			set_encode_encode_mode(t_encode_context *ctx)
{
	ctx->mode &= 0xFFFFFFFE;
	return (0);
}
