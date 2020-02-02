/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cipher_context.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 19:40:06 by a17641238         #+#    #+#             */
/*   Updated: 2020/01/30 19:40:06 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "utilities.h"
#include <string.h>
#include <unistd.h>

t_cipher_context	*init_cipher_context(void *alg_ptr)
{
	t_cipher_context	*ctx;

	ctx = (t_cipher_context *)xmalloc(sizeof(t_cipher_context));
	memset(ctx, 0, sizeof(t_cipher_context));
	ctx->bufsize = DEFAULT_CIPHER_BUFLEN;
	ctx->output_fd = STDOUT_FILENO;
	ctx->input_fd = STDIN_FILENO;
	ctx->alg_ptr = alg_ptr;
	return (ctx);
}
