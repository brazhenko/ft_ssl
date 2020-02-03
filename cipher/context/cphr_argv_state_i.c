/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cphr_argv_state_i.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:24:01 by a17641238         #+#    #+#             */
/*   Updated: 2020/02/03 10:24:01 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher_context.h"
#include <string.h>

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
