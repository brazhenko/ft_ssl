/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:03:13 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/28 23:03:15 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

void		cipher_executor(int ac, char **av,
		void *(*algo)(t_cipher_context *))
{
	t_cipher_context		*ctx;

	ctx = init_cipher_context(algo);
	ctx = parse_des_argv(ctx, ac, av);
	algo(ctx);
	destruct_cipher_context(ctx);
}
