/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cipher_password_from_stdin.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:37:56 by a17641238         #+#    #+#             */
/*   Updated: 2020/01/30 17:37:56 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher_context.h"
#include <string.h>
#include <readpassphrase.h>
#include "utilities.h"

int			set_cipher_password_from_stdin(t_cipher_context *ctx)
{
	char		tmp[PASS_MAX];

	memset(tmp, 0, sizeof(tmp));
	memset(ctx->password, 0, sizeof(ctx->password));
	if (!readpassphrase(CIPHER_PASSWORD_PROMPT, ctx->password,
			sizeof(ctx->password), RPP_ECHO_OFF))
	{
		nstrprinterror(1, "password read failed\n");
		exit(EXIT_FAILURE);
	}
	if (!readpassphrase(CIPHER_PASSWORD_VERIFY_PROMPT, tmp,
			sizeof(tmp), RPP_ECHO_OFF))
	{
		nstrprinterror(1, "password read failed\n");
		exit(EXIT_FAILURE);
	}
	if (strcmp(ctx->password, tmp))
	{
		nstrprinterror(1, "password verification failed\n");
		exit(EXIT_FAILURE);
	}
	memset(tmp, 0, sizeof(tmp));
	ctx->mode |= 0b100000;
	return (0);
}
