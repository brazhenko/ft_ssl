/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rsautl_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:36:35 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/29 19:02:54 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsautl_context.h"
#include <stdlib.h>
#include <string.h>
#include <utilities.h>
#include <fcntl.h>
#include <errno.h>
#include "parse_rsautl_internal.h"

t_rsautl_context	*init_rsautl_ctx(void)
{
	t_rsautl_context	*ctx;

	ctx = malloc(sizeof(*ctx));
	memset(ctx, 0, sizeof(*ctx));
	ctx->inkey_fd = -1;
	ctx->input_fd = 0;
	ctx->output_fd = 1;
	return (ctx);
}

void				delete_rsautl_ctx(t_rsautl_context *ctx)
{
	free(ctx);
}

void				rsautl_unexpected_token_exit(const char *token)
{
	nstrprinterror(3, "unexpected token near ", token, "\n");
	exit(EXIT_FAILURE);
}

t_rsautl_context	*parse_rsa_utl_state_inkey(int ac, char **argv,
													t_rsautl_context *ctx)
{
	int		input_fd;

	input_fd = open(*argv, O_RDONLY);
	ctx->inkey_fd = input_fd;
	if (input_fd < 0)
	{
		nstrprinterror(5, "Unable to open \'", *argv,
				"\': ", strerror(errno), "\n");
		exit(1);
	}
	return (parse_rsautl_argv(ac - 1, argv + 1, ctx));
}

t_rsautl_context	*parse_rsa_utl_state_out(int argc, char **argv,
												t_rsautl_context *ctx)
{
	const int output_fd = open(*argv, O_CREAT | O_WRONLY | O_TRUNC, 0666);

	ctx->output_fd = output_fd;
	if (output_fd < 0)
	{
		nstrprinterror(5, "Unable to open \'", *argv,
				"\': ", strerror(errno), "\n");
		exit(1);
	}
	return (parse_rsautl_argv(argc - 1, argv + 1, ctx));
}
