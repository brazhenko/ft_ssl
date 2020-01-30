/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:25:26 by a17641238         #+#    #+#             */
/*   Updated: 2020/01/30 17:25:26 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

void		encode_executor(int ac, char **av,
		void *(*algo)(t_encode_context*))
{
	t_encode_context	*ctx;

	ctx = parse_encode_argv(ac, av);
	algo(ctx);
	destruct_encode_context(ctx);
}
