/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_gen_rsa_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:36:19 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/28 16:00:30 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "genrsa_context.h"
#include <utilities.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int					set_genrsa_output_file(t_genrsa_context *ctx,
									const char *output_file_name);
void				*gen_rsa_token_needs_arg_exit(char *token);
void				*gen_rsa_unexpected_token_exit(char *token);

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