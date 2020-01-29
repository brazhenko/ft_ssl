#include "des.h"
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

/*
** try_get_des_salt_from_fd() reads 16 bytes and
** tries get "Salted__........" pattern. Returns 0 if
** Success, 1 if not.
*/

int		try_get_des_salt_from_fd(t_cipher_context *ctx)
{
	ssize_t		rd;
	char		buf[16];

	rd = read(ctx->input_fd, buf, sizeof(buf));
	if (rd == sizeof(buf) && !strncmp(buf, "Salted__", 8))
	{
		ctx->mode |= 0b1000000;
		memcpy(ctx->salt, &buf[8], sizeof(ctx->salt));
		return (0);
	}
	else
	{
		memset(ctx->salt, 0, sizeof(ctx->salt));
		close(ctx->input_fd);
		ctx->input_fd = open(ctx->input_file, O_RDONLY);
		if (ctx->input_fd < 0)
		{
			perror("Cannot reopen file");
			exit(EXIT_FAILURE);
		}
		return (1);
	}
}
