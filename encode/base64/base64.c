# include "ssl.h"
# include "base64.h"
#include <stddef.h>


void		*base64(t_encode_context *ctx)
{
	if (ISENCODEMODE(ctx))
		base64_encode(ctx);
	else if (ISDECODEMODE(ctx))
	{
		// puts("DEBUG: decode() under testing:");
		base64_decode(ctx);
	}
	return (NULL);
}

