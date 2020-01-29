#include "cipher_context.h"
#include "utilities.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int		set_cipher_input_file(t_cipher_context *ctx,
								const char *input_file_name)
{
	int			input_fd;

	memset(ctx->input_file, '\0', PATH_MAX);
	strcpy(ctx->input_file, input_file_name);
	ctx->mode |= 0b100;
	input_fd = open(input_file_name, O_RDONLY);
	ctx->input_fd = input_fd;
	if (input_fd < 0)
	{
		nstrprinterror(5, "Unable to open \'", input_file_name,
				"\': ", strerror(errno), "\n");
		exit(1);
	}
	return (0);
}
