/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rsa_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:36:23 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/29 19:41:31 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa_context.h"
#include <stdlib.h>
#include <string.h>
#include "internal_rsa_ctx.h"

t_rsa_context	*init_rsa_ctx(void)
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

void			delete_rsa_ctx(t_rsa_context *ctx)
{
	free(ctx);
}

t_rsa_context	*parse_rsa_argv(int argc, char **argv, t_rsa_context *ctx)
{
	while (*argv)
	{
		if (strcmp(*argv, "-in") == 0)
			return (rsa_state_in(argc - 1, argv + 1, ctx));
		else if (strcmp(*argv, "-out") == 0)
			return (rsa_state_out(argc - 1, argv + 1, ctx));
		else if (strcmp(*argv, "-modulus") == 0)
			ctx->mode |= RSA_CTX_MODE_MODULUS;
		else if (strcmp(*argv, "-pubin") == 0)
			ctx->mode |= RSA_CTX_MODE_PUBIN;
		else if (strcmp(*argv, "-pubout") == 0)
			ctx->mode |= RSA_CTX_MODE_PUBOUT;
		else if (strcmp(*argv, "-noout") == 0)
			ctx->mode |= RSA_CTX_MODE_NOOUT;
		else if (strcmp(*argv, "-text") == 0)
			ctx->mode |= RSA_CTX_MODE_TEXT;
		else if (strcmp(*argv, "-inform") == 0)
			return (rsa_state_inform(argc - 1, argv + 1, ctx));
		else if (strcmp(*argv, "-outform") == 0)
			return (rsa_state_outform(argc - 1, argv + 1, ctx));
		else
			rsa_unexpected_token_exit(*argv);
		argv++;
	}
	return (ctx);
}
