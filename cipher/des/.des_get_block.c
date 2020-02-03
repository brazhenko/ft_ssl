#include <des.h>
#include <unistd.h>
#include <string.h>
#include <utilities.h>
#include <termios.h>
#include <stdio.h>

/*
** des_get_enc_block() returns padded(if needed) block from fd
*/

ssize_t		des_get_enc_block(t_cipher_context *ctx, t_lpdesblock block)
{
	ssize_t			rc;
	static int		end_reading = 0;


	static struct termios	stored_settings;
	static struct termios	new_settings;

	if (end_reading)
		return (0);
	memset(*block, 0, DES_CIPHER_BLOCK_LEN);


	tcgetattr(0, &stored_settings);
	new_settings = stored_settings;
	new_settings.c_iflag |= (ICRNL);
	// printf("1: %d 2: 3: \n", new_settings.c_cc[VSTART]);
	new_settings.c_lflag &= (~ICANON);
	//new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VEOF] = 'n';

	new_settings.c_cc[VMIN] = 64;
	//tcsetattr(0, TCSANOW, &new_settings);

	rc = read(ctx->input_fd, block, DES_CIPHER_BLOCK_LEN);
	// tcsetattr(0, TCSANOW, &stored_settings);

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