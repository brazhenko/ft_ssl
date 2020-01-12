#include <des.h>
#include <unistd.h>
#include <string.h>

ssize_t		des_get_block(t_cipher_context *ctx, LPDESBLOCK block)
{
	static unsigned char *buffer = NULL;
	static size_t read_len		= 0;
	static size_t i = 0;
	ssize_t		rc;
	DESBLOCK	res;
	//
	memset(*block, 0, 8);
	rc = read(ctx->input_fd, block, 8);

	// Padding

	if (rc < 8)
	{
		for (int j = rc; j < 8; ++j)
		{
			(*block)[j] = 8 - rc;
		}
	}
	return rc; // TODO make normal file reader HARDCORE
}