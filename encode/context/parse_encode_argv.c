/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_encode_argv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:30:48 by a17641238         #+#    #+#             */
/*   Updated: 2020/01/30 17:30:48 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"
#include <string.h>

t_encode_context	*parse_encode_argv(int argc, char **argv)
{
	t_encode_context	*ctx;

	ctx = init_encode_context();
	if (!(*argv))
		return (ctx);
	else if (strcmp(*argv, "-d") == 0)
		return (encode_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (encode_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (encode_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (encode_state_o(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-h") == 0)
		encode_print_usage_exit();
	else
		encode_invalid_option_exit(*argv);
	return (ctx);
}
