/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_ctx2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:49:49 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/28 16:49:49 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa_context.h"
#include <stdlib.h>
#include <string.h>
#include <utilities.h>
#include <fcntl.h>
#include <errno.h>

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
