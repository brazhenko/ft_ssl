#include "cipher_context.h"

int			cphr_is_a_flag(t_cipher_context *ctx)
{
	return ((ctx)->mode & (1U << 3U));
}
