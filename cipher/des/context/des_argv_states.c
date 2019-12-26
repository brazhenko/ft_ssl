#include "des.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
** set ctx to -a == true
*/

t_des_context	*des_state_a(int argc, char **argv, t_des_context *ctx)
{
	ctx->mode |= 0b1000;
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (des_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (des_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (des_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (des_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (des_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (des_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (des_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (des_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (des_state_v(argc - 1, argv + 1, ctx));
	else
	{
		// TODO usage print, exit() etc.
		puts("des_state_a(): unexpected token");
		exit(0);
	}
	return (ctx);
}

/*
** sets ctx to decrypt mode
*/

t_des_context	*des_state_d(int argc, char **argv, t_des_context *ctx)
{
	ctx->mode |= 0b1;
	if (!(*argv))
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (des_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (des_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (des_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (des_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (des_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (des_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (des_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (des_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (des_state_v(argc - 1, argv + 1, ctx));
	else
	{
		// TODO usage print, exit() etc.
		puts("des_state_d(): unexpected token");
		exit(0);
	}
	return (ctx);
}

/*
** sets ctx to encrypt mode
*/

t_des_context	*des_state_e(int argc, char **argv, t_des_context *ctx)
{
	ctx->mode &= 0xFFFFFFFE;
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (des_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (des_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (des_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (des_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (des_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (des_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (des_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (des_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (des_state_v(argc - 1, argv + 1, ctx));
	else
	{
		// TODO usage print, exit() etc.
		puts("des_state_e(): unexpected token");
		exit(0);
	}
	return (ctx);
}

t_des_context	*des_state_i(int argc, char **argv, t_des_context *ctx)
{
	if (!(*argv))
	{
		puts("des_state_i(): -i needs arg");
		exit(0);
		return (ctx);
	}
	memset(ctx->input_file, 0, sizeof(ctx->input_file));
	strcpy(ctx->input_file, *argv);
	ctx->mode |= 0b100;
	argv++;
	argc--;
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (des_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (des_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (des_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (des_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (des_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (des_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (des_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (des_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (des_state_v(argc - 1, argv + 1, ctx));
	else
	{
		// TODO usage print, exit() etc.
		puts("des_state_i(): unexpected token");
		exit(0);
	}
	return (ctx);
}

/*
** set hex key
*/

t_des_context	*des_state_k(int argc, char **argv, t_des_context *ctx)
{
	if (!(*argv))
	{
		puts("des_state_k(): -k needs arg");
		exit(0);
		return (ctx);
	}
	memcpy(ctx->key, 0, sizeof(ctx->key));
	strcpy(ctx->key, *argv);
	ctx->mode |= 0b10000;
	argv++;
	argc--;
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (des_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (des_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (des_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (des_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (des_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (des_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (des_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (des_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (des_state_v(argc - 1, argv + 1, ctx));
	else
	{
		// TODO usage print, exit() etc.
		puts("des_state_k(): unexpected token");
		exit(0);
	}
	return (ctx);
}

t_des_context	*des_state_o(int argc, char **argv, t_des_context *ctx)
{
	if (!(*argv))
	{
		puts("des_state_o(): -o needs arg");
		exit(0);
		return (ctx);
	}
	memset(ctx->output_file, 0, sizeof(ctx->output_file));
	strcpy(ctx->output_file, *argv);
	ctx->mode |= 0b10;
	argv++;
	argc--;
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (des_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (des_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (des_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (des_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (des_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (des_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (des_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (des_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (des_state_v(argc - 1, argv + 1, ctx));
	else
	{
		// TODO usage print, exit() etc.
		puts("des_state_o(): unexpected token");
		exit(0);
	}
	return (ctx);
}

t_des_context	*des_state_p(int argc, char **argv, t_des_context *ctx)
{
	if (!(*argv))
	{
		puts("des_state_p(): -p needs arg");
		exit(0);
		return (ctx);
	}
	memset(ctx->password, 0, sizeof(ctx->password));
	strcpy(ctx->password, *argv);
	ctx->mode |= 0b100000;
	argv++;
	argc--;
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (des_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (des_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (des_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (des_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (des_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (des_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (des_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (des_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (des_state_v(argc - 1, argv + 1, ctx));
	else
	{
		// TODO usage print, exit() etc.
		puts("des_state_p(): unexpected token");
		exit(0);
	}
	return (ctx);
}

t_des_context	*des_state_s(int argc, char **argv, t_des_context *ctx)
{
	if (!(*argv))
	{
		puts("des_state_s(): -s needs arg");
		exit(0);
		return (ctx);
	}
	memset(ctx->salt, 0, sizeof(ctx->salt));
	strcpy(ctx->salt, *argv);
	ctx->mode |= 0b1000000;
	argv++;
	argc--;
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (des_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (des_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (des_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (des_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (des_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (des_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (des_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (des_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (des_state_v(argc - 1, argv + 1, ctx));
	else
	{
		// TODO usage print, exit() etc.
		puts("des_state_s(): unexpected token");
		exit(0);
	}
	return (ctx);
}

t_des_context	*des_state_v(int argc, char **argv, t_des_context *ctx)
{
	if (!(*argv))
	{
		puts("des_state_v(): -v needs arg");
		exit(0);
		return (ctx);
	}
	memset(ctx->vector, 0, sizeof(ctx->vector));
	strcpy(ctx->vector, *argv);
	ctx->mode |= 0b10000000;
	argv++;
	argc--;
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (des_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (des_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (des_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (des_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (des_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (des_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (des_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (des_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (des_state_v(argc - 1, argv + 1, ctx));
	else
	{
		// TODO usage print, exit() etc.
		puts("des_state_v(): unexpected token");
		exit(0);
	}
	return (ctx);
}


t_des_context	*parse_des_argv(int argc, char **argv)
{
	t_des_context	*ctx;

	ctx = init_des_context();
	if (!*argv)
		return (ctx);
	else if (strcmp(*argv, "-a") == 0)
		return (des_state_a(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-d") == 0)
		return (des_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (des_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (des_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-k") == 0)
		return (des_state_k(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (des_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-p") == 0)
		return (des_state_p(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-s") == 0)
		return (des_state_s(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-v") == 0)
		return (des_state_v(argc - 1, argv + 1, ctx));
	else
	{
		// TODO usage print, exit() etc.
		puts("parse_des_argv(): unexpected token");
		exit(0);
	}
	return (ctx);
}