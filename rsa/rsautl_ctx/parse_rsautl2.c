/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rsautl2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 19:01:20 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/29 19:01:49 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsautl_context.h"
#include <stdlib.h>
#include <string.h>
#include <utilities.h>
#include <fcntl.h>
#include <errno.h>
#include "parse_rsautl_internal.h"

t_rsautl_context	*parse_rsa_utl_state_in(int argc, char **argv,
		t_rsautl_context *ctx)
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
	return (parse_rsautl_argv(argc - 1, argv + 1, ctx));
}

t_rsautl_context	*parse_rsautl_argv(int argc, char **argv,
		t_rsautl_context *ctx)
{
	while (*argv)
	{
		if (strcmp(*argv, "-encrypt") == 0)
			ctx->mode &= (~RSAUTL_CTX_DECRYPT);
		else if (strcmp(*argv, "-decrypt") == 0)
			ctx->mode |= RSAUTL_CTX_DECRYPT;
		else if (strcmp(*argv, "-hexdump") == 0)
			ctx->mode |= RSAUTL_CTX_HEXDUMP;
		else if (strcmp(*argv, "-pubin") == 0)
			ctx->mode |= RSAUTL_CTX_PUBIN;
		else if (strcmp(*argv, "-inkey") == 0)
			return (parse_rsa_utl_state_inkey(argc - 1, argv + 1, ctx));
		else if (strcmp(*argv, "-out") == 0)
			return (parse_rsa_utl_state_out(argc - 1, argv + 1, ctx));
		else if (strcmp(*argv, "-in") == 0)
			return (parse_rsa_utl_state_in(argc - 1, argv + 1, ctx));
		else
			rsautl_unexpected_token_exit(*argv);
		argv++;
	}
	return (ctx);
}
