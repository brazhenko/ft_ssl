/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruct_cipher_context.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 19:40:01 by a17641238         #+#    #+#             */
/*   Updated: 2020/01/30 19:40:01 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher_context.h"
#include <string.h>
#include <unistd.h>

void		destruct_cipher_context(t_cipher_context *ctx)
{
	close(ctx->input_fd);
	close(ctx->output_fd);
	memset(ctx, 0, sizeof(t_cipher_context));
	free(ctx);
}
