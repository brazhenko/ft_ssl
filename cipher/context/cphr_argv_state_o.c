/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cphr_argv_state_o.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:24:11 by a17641238         #+#    #+#             */
/*   Updated: 2020/02/03 10:38:34 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher_context.h"
#include <string.h>

static void			o_action(char *arg, t_cipher_context *ctx)
{
	if (!(arg))
		token_needs_arg_exit("-o");
	set_cipher_output_file(ctx, arg);
}

t_cipher_context	*ci_state_o(int argc, char **argv, t_cipher_context *ctx)
{
	o_action(*argv, ctx);
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
