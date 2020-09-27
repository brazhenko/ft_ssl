//
// Created by 17641238 on 25.09.2020.
//

#include "rsa_context.h"
#include <stdlib.h>
#include <string.h>
#include <utilities.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

t_rsa_context	*init_rsa_ctx()
{
	t_rsa_context		*ctx;

	ctx = malloc(sizeof(*ctx));
	memset(ctx, 0, sizeof(*ctx));
	strcpy(ctx->inform, "PEM");
	strcpy(ctx->outform, "PEM");
	ctx->input_fd = 0;
	ctx->output_fd = 1;
	return (ctx);
}

void 			delete_rsa_ctx(const t_rsa_context *ctx)
{
	free((void*)ctx);
}

t_rsa_context	*rsa_state_in(int argc, char **argv, t_rsa_context *ctx)
{
	int		input_fd;

	input_fd = open(*argv, O_RDONLY);
	ctx->input_fd = input_fd;
	if (input_fd < 0)
	{
		nstrprinterror(5, "Unable to open \'", *argv,
				"\': ", strerror(errno), "\n");
		exit(1);
	}
	return (parse_rsa_argv(argc - 1, argv + 1, ctx));
}

t_rsa_context	*rsa_state_out(int argc, char **argv, t_rsa_context *ctx)
{
	const int output_fd = open(*argv, O_CREAT | O_WRONLY | O_TRUNC, 0666);

	ctx->output_fd = output_fd;
	if (output_fd < 0)
	{
		nstrprinterror(5, "Unable to open \'", *argv,
				"\': ", strerror(errno), "\n");
		exit(1);
	}
	return (parse_rsa_argv(argc - 1, argv + 1, ctx));
}

void			rsa_unexpected_token_exit(const char *token)
{
	nstrprinterror(3, "unexpected token near ", token, "\n");
	exit(EXIT_FAILURE);
}

t_rsa_context	*rsa_state_inform(int argc, char **argv, t_rsa_context *ctx)
{
	memset(ctx->inform, 0, sizeof(ctx->inform));
	strcpy(ctx->inform, *argv);
	return (parse_rsa_argv(argc - 1, argv + 1, ctx));
}


t_rsa_context	*rsa_state_outform(int argc, char **argv, t_rsa_context *ctx)
{
	memset(ctx->outform, 0, sizeof(ctx->outform));
	strcpy(ctx->outform, *argv);
	return (parse_rsa_argv(argc - 1, argv + 1, ctx));
}


t_rsa_context	*parse_rsa_argv(int argc, char **argv, t_rsa_context *ctx)
{
	while (*argv)
	{
		if (strcmp(*argv, "-in") == 0)
			return rsa_state_in(argc - 1, argv + 1, ctx);
		else if (strcmp(*argv, "-out") == 0)
			return rsa_state_out(argc - 1, argv + 1, ctx);
		else if (strcmp(*argv, "-modulus") == 0)
			ctx->mode |= RSA_CTX_MODE_MODULUS;
		else if (strcmp(*argv, "-pubin") == 0)
			ctx->mode |= RSA_CTX_MODE_PUBIN;
		else if (strcmp(*argv, "-pubout") == 0)
			ctx->mode |= RSA_CTX_MODE_PUBOUT;
		else if (strcmp(*argv, "noout-") == 0)
			ctx->mode |= RSA_CTX_MODE_NOOUT;
		else if (strcmp(*argv, "-check") == 0)
			ctx->mode |= RSA_CTX_MODE_CHECK;
		else if (strcmp(*argv, "-text") == 0)
			ctx->mode |= RSA_CTX_MODE_TEXT;
		else if (strcmp(*argv, "-inform") == 0)
			return rsa_state_inform(argc - 1, argv + 1,  ctx);
		else if (strcmp(*argv, "-outform") == 0)
			return rsa_state_outform(argc - 1, argv + 1,  ctx);
		else
			rsa_unexpected_token_exit(*argv);
		argv++;
	}
	return (ctx);
}