#include "cipher_context.h"
#include "utilities.h"
#include <string.h>
#include <stdlib.h>

static const uint8_t	hex2bin[] =
{
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u,
	8, 9, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 10u, 11u, 12u, 13u, 14u, 15u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 10u, 11u, 12u, 13u, 14u, 15u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
};

static void		cipher_hex_iv_too_long_exit(void)
{
	nstrprinterror(1, "hex string is too long\n");
	exit(EXIT_FAILURE);
}

static void		cipher_iv_non_hex_exit(void)
{
	nstrprinterror(1, "non-hex digit\n");
	exit(EXIT_FAILURE);
}

int 			set_cipher_init_vector(t_cipher_context *ctx, char *arg)
{
	size_t		i;
	uint8_t		bin;

	memset(ctx->vector_ini, '\0', sizeof(ctx->vector_ini));
	ctx->mode |= 0b10000000;
	i = 0;
	while (arg[i])
	{
		bin = hex2bin[arg[i]];
		if (bin)
		{
			ctx->key[i / 2] |= (bin << (4u * (1u - i % 2u)));
		}
		else
			cipher_iv_non_hex_exit();
		i++;
		if (i == MAX_IV_DIG_LEN)
			cipher_hex_iv_too_long_exit();
	}
	return (0);
}