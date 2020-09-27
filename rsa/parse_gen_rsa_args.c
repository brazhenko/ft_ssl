//
// Created by 17641238 on 24.09.2020.
//

#include "genrsa_context.h"
#include <utilities.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int					set_genrsa_output_file(t_genrsa_context *ctx,
							const char *output_file_name)
{
	int			output_fd;

	memset(ctx->output_file, '\0', PATH_MAX);
	strcpy(ctx->output_file, output_file_name);
	output_fd = open(output_file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	ctx->output_fd = output_fd;
	if (output_fd < 0)
	{
		nstrprinterror(5, "Unable to open \'", output_file_name,
				"\': ", strerror(errno), "\n");
		exit(1);
	}
	return (0);
}

void				*gen_rsa_token_needs_arg_exit(char *token)
{
	nstrprinterror(2, token, " needs argument\n");
	exit(EXIT_FAILURE);
}

void				*gen_rsa_unexpected_token_exit(char *token)
{
	nstrprinterror(3, "unexpected token near ", token, "\n");
	exit(EXIT_FAILURE);
}

t_genrsa_context	*init_gen_rsa_ctx()
{
	t_genrsa_context	*ret;

	ret = xmalloc(sizeof(t_genrsa_context));
	memset(ret, 0, sizeof(*ret));
	ret->output_fd = 1;
	return (ret);
}

void 				delete_gen_rsa_ctx(t_genrsa_context *ctx)
{
	close(ctx->output_fd);
	free(ctx);
}

t_genrsa_context	*genrsa_state_o(int argc, char **argv, t_genrsa_context *ctx)
{
	if (!(*argv))
		gen_rsa_token_needs_arg_exit("-o");
	set_genrsa_output_file(ctx, *argv);
	argv++;
	argc--;
	if (!*argv)
		return (ctx);
	if (strcmp(*argv, "-o") == 0)
		return (genrsa_state_o(argc - 1, argv + 1, ctx));
	return (gen_rsa_unexpected_token_exit(*argv));
}

t_genrsa_context	*parse_gen_rsa_argv(int argc, char **argv)
{
	t_genrsa_context *ctx;

	ctx = init_gen_rsa_ctx();

	if (!*argv)
		return (ctx);
	if (strcmp(*argv, "-o") == 0)
		return (genrsa_state_o(argc - 1, argv + 1, ctx));
	return (gen_rsa_unexpected_token_exit(*argv));
}