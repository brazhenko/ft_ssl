#include <des.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

ssize_t		des_get_enc_block(t_cipher_context *ctx, LPDESBLOCK block)
{
	static unsigned char *buffer = NULL;
	static size_t read_len		= 0;
	static size_t i = 0;
	ssize_t		rc;
	DESBLOCK	res;

	static int done = 0;
	memset(*block, 0, 8);
	rc = read(ctx->input_fd, block, 8);
	if (rc == 0 && done == 0)
	{
		done = 1;

		{
			for (int j = 0; j < 8; ++j)
			{
				(*block)[j] = 8;
			}
		}
		return 1;
	}
	else if (done == 1)
		return 0;
	// Padding

	if (rc < 8)
	{
		done = 1;
		for (int j = rc; j < 8; ++j)
		{
			(*block)[j] = 8 - rc;
		}
	}
	return rc; // TODO make normal file reader HARDCORE
}


ssize_t		des_get_decr_block(t_cipher_context *ctx, LPDESBLOCK block)
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