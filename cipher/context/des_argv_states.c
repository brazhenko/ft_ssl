#include "des.h"
#include <string.h>
#include <stdlib.h>
#include <utilities.h>

void*				token_needs_arg_exit(char *token)
{
	nstrprinterror(2, token, " needs argument\n");
	exit(EXIT_FAILURE);
}

void*				unexpected_token_exit(char *token)
{
	nstrprinterror(3, "unexpected token near ", token, "\n");
	exit(EXIT_FAILURE);
}

/*
** set ctx to base64 encode
*/

t_cipher_context	*ci_state_a(int argc, char **argv, t_cipher_context *ctx)
{
	ctx->mode |= 0b1000;
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (ci_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (ci_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (ci_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (ci_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (ci_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (ci_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (ci_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (ci_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (ci_state_v(argc - 1, argv + 1, ctx));
	else
		return (unexpected_token_exit(*argv));
}

/*
** sets ctx to decrypt mode
*/

t_cipher_context	*ci_state_d(int argc, char **argv, t_cipher_context *ctx)
{
	ctx->mode |= 0b1;
	if (!(*argv))
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (ci_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (ci_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (ci_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (ci_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (ci_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (ci_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (ci_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (ci_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (ci_state_v(argc - 1, argv + 1, ctx));
	else
		return (unexpected_token_exit(*argv));
}

/*
** sets ctx to encrypt mode
*/

t_cipher_context	*ci_state_e(int argc, char **argv, t_cipher_context *ctx)
{
	ctx->mode &= 0xFFFFFFFE;
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (ci_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (ci_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (ci_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (ci_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (ci_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (ci_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (ci_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (ci_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (ci_state_v(argc - 1, argv + 1, ctx));
	else
		return (unexpected_token_exit(*argv));
}

t_cipher_context	*ci_state_i(int argc, char **argv, t_cipher_context *ctx)
{
	if (!(*argv))
		token_needs_arg_exit("-i");
	set_cipher_input_file(ctx, *argv);
	argv++;
	argc--;
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (ci_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (ci_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (ci_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (ci_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (ci_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (ci_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (ci_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (ci_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (ci_state_v(argc - 1, argv + 1, ctx));
	else
		return (unexpected_token_exit(*argv));
}

/*
** set hex key
*/

t_cipher_context	*ci_state_k(int argc, char **argv, t_cipher_context *ctx)
{
	if (!(*argv))
		token_needs_arg_exit("-k");
	set_cipher_key(ctx, *argv);
	argv++;
	argc--;
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (ci_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (ci_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (ci_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (ci_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (ci_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (ci_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (ci_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (ci_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (ci_state_v(argc - 1, argv + 1, ctx));
	else
		return (unexpected_token_exit(*argv));
}

t_cipher_context	*ci_state_o(int argc, char **argv, t_cipher_context *ctx)
{
	if (!(*argv))
		token_needs_arg_exit("-o");
	set_cipher_output_file(ctx, *argv);
	argv++;
	argc--;
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (ci_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (ci_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (ci_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (ci_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (ci_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (ci_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (ci_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (ci_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (ci_state_v(argc - 1, argv + 1, ctx));
	else
		return (unexpected_token_exit(*argv));
}

t_cipher_context	*ci_state_p(int argc, char **argv, t_cipher_context *ctx)
{
	if (!(*argv))
		token_needs_arg_exit("-p");
	memset(ctx->password, 0, sizeof(ctx->password));
	strcpy(ctx->password, *argv);
	ctx->mode |= 0b100000;
	argv++;
	argc--;
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (ci_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (ci_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (ci_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (ci_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (ci_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (ci_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (ci_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (ci_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (ci_state_v(argc - 1, argv + 1, ctx));
	else
		return (unexpected_token_exit(*argv));
}

t_cipher_context	*ci_state_s(int argc, char **argv, t_cipher_context *ctx)
{
	if (!(*argv))
		token_needs_arg_exit("-s");
	set_cipher_pass_salt(ctx, *argv);
	argv++;
	argc--;
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (ci_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (ci_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (ci_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (ci_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (ci_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (ci_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (ci_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (ci_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (ci_state_v(argc - 1, argv + 1, ctx));
	else
		return (unexpected_token_exit(*argv));
}

t_cipher_context	*ci_state_v(int argc, char **argv, t_cipher_context *ctx)
{
	if (!(*argv))
		token_needs_arg_exit("-v");
	set_cipher_init_vector(ctx, *argv);
	argv++;
	argc--;
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (ci_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (ci_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (ci_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (ci_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (ci_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (ci_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (ci_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (ci_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (ci_state_v(argc - 1, argv + 1, ctx));
	else
		return (unexpected_token_exit(*argv));
}

t_cipher_context	*parse_des_argv(t_cipher_context *ctx,
								int argc, char **argv)
{
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (ci_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (ci_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (ci_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (ci_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (ci_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (ci_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (ci_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (ci_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (ci_state_v(argc - 1, argv + 1, ctx));
	else
		return (unexpected_token_exit(*argv));
}
