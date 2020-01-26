#include <des.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

/*
** des_get_enc_block() returns padded(if needed) block from fd
*/

ssize_t		des_get_enc_block(t_cipher_context *ctx, t_lpdesblock block)
{
	ssize_t			rc;
	static int		end_reading = 0;

	if (end_reading)
		return (0);
	memset(*block, 0, 8);
	rc = read(ctx->input_fd, block, sizeof(*block));
	if (rc != 8)
	{
		for (int j = rc; j < 8; ++j)
			(*block)[j] = 8 - rc;
		end_reading = 1;
	}
	return (1);
}


ssize_t		des_get_decr_block(t_cipher_context *ctx, t_lpdesblock block)
{
	ssize_t		rc;
	memset(*block, 0, 8);
	rc = read(ctx->input_fd, block, 8);

	if (rc == 0)
		return (rc);
	if (rc != 8)
	{
		puts("wrong block size");
		exit(1);
	}
	return rc; // TODO make normal file reader HARDCORE
}