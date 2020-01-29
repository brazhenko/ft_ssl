#include "cipher_context.h"

int				cphr_is_pass_set(t_cipher_context *ctx)
{
	return ((ctx)->mode & (1U << 5U));
}
