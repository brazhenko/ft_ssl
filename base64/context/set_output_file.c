#include "base64.h"
#include <string.h>
#include <fcntl.h>
#include <utilities.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int					set_base64_output_file(t_base64_context *ctx,
		const char *output_file_name)
{
	int 	output_fd;

	memset(ctx->output_file, '\0', PATH_MAX);
	strcpy(ctx->output_file, output_file_name);
	ctx->mode |= 0b10;
	output_fd = open(output_file_name, O_CREAT | O_WRONLY);
	ctx->output_fd = output_fd;
	printf("output_fd: %d\n", output_fd);
	if (output_fd < 0)
	{
		nstrprinterror(5, "Unable to open \'", output_file_name,
				"\': ", strerror(errno), "\n");
		exit(1);
	}
	return (0);
}