#include "base64.h"
#include <stdlib.h>

void	destruct_encode_context(t_encode_context *ctx)
{
	free(ctx);
}