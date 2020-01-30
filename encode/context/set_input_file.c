/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:28:58 by a17641238         #+#    #+#             */
/*   Updated: 2020/01/30 17:28:58 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encode_context.h"
#include <string.h>
#include <fcntl.h>
#include "utilities.h"
#include <stdlib.h>
#include <errno.h>

int					set_encode_input_file(t_encode_context *ctx,
							const char *input_file_name)
{
	int		input_fd;

	memset(ctx->input_file, '\0', PATH_MAX);
	strcpy(ctx->input_file, input_file_name);
	ctx->mode |= 0b100;
	input_fd = open(input_file_name, O_RDONLY);
	ctx->input_fd = input_fd;
	if (input_fd < 0)
	{
		nstrprinterror(5, "Unable to open \'", input_file_name,
				"\': ", strerror(errno), "\n");
		exit(1);
	}
	return (0);
}
