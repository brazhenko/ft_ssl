/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genrsa_ctx2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:48:46 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/28 16:48:46 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "genrsa_context.h"
#include <utilities.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int					set_genrsa_output_file(t_genrsa_context *ctx,
		const char *output_file_name)
{
	int			output_fd;

	memset(ctx->output_file, '\0', PATH_MAX);
	strcpy(ctx->output_file, output_file_name);
	output_fd = open(output_file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	ctx->output_fd = output_fd;
	if (output_fd < 0)
	{
		nstrprinterror(5, "Unable to open \'", output_file_name,
				"\': ", strerror(errno), "\n");
		exit(1);
	}
	return (0);
}

void				*gen_rsa_token_needs_arg_exit(char *token)
{
	nstrprinterror(2, token, " needs argument\n");
	exit(EXIT_FAILURE);
}

void				*gen_rsa_unexpected_token_exit(char *token)
{
	nstrprinterror(3, "unexpected token near ", token, "\n");
	exit(EXIT_FAILURE);
}