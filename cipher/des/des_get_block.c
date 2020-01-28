#include <des.h>
#include <unistd.h>
#include <string.h>
#include <utilities.h>

/*
** des_get_enc_block() returns padded(if needed) block from fd
*/

ssize_t		des_get_enc_block(t_cipher_context *ctx, t_lpdesblock block)
{
	ssize_t			rc;
	static int		end_reading = 0;

	if (end_reading)
		return (0);
	memset(*block, 0, DES_CIPHER_BLOCK_LEN);
	rc = read(ctx->input_fd, block, DES_CIPHER_BLOCK_LEN);
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
		nstrprinterror(1 , "wrong block size, cipher text is corrupted\n");
		exit(EXIT_FAILURE);
	}
	return (rc);
}