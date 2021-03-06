/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:04:13 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/29 19:26:01 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "rsa_context.h"
#include "rsa.h"
#include "utilities.h"
#include "key_io.h"
#include "internal_rsa.h"

void	parse_key(t_rsa_context *ctx,
		t_rsa_pub_key *pub_out,
		t_rsa_priv_key *priv_out)
{
	if (ctx->mode & RSA_CTX_MODE_PUBIN)
	{
		if (strcmp(ctx->inform, "PEM") == 0)
			rsa_parse_pub_pem(ctx->input_fd, pub_out);
		else if (strcmp(ctx->inform, "DER") == 0)
			rsa_parse_pub_der(ctx->input_fd, pub_out);
		else
			fatal("Unknown -inform param");
	}
	else
	{
		if (strcmp(ctx->inform, "PEM") == 0)
			rsa_parse_priv_pem(ctx->input_fd, priv_out);
		else if (strcmp(ctx->inform, "DER") == 0)
			rsa_parse_priv_der(ctx->input_fd, priv_out);
		else
			fatal("Unknown -inform param");
	}
}

void	print_priv_key(t_rsa_context *ctx, t_rsa_priv_key *k)
{
	if (strcmp(ctx->outform, "DER") == 0)
		rsa_put_priv_der(ctx->output_fd, k);
	else if (strcmp(ctx->outform, "PEM") == 0)
		rsa_put_priv_pem(ctx->output_fd, k);
	else
		fatal("Unknown outform, exit");
}

void	print_pub_key(t_rsa_context *ctx, const t_rsa_pub_key *k)
{
	if (strcmp(ctx->outform, "DER") == 0)
		rsa_put_pub_der(ctx->output_fd, k);
	else if (strcmp(ctx->outform, "PEM") == 0)
		rsa_put_pub_pem(ctx->output_fd, k);
	else
		fatal("Unknown outform, exit");
}

void	process_output(t_rsa_context *ctx,
		t_rsa_pub_key *pub_out,
		t_rsa_priv_key *priv_out)
{
	if ((ctx->mode & RSA_CTX_MODE_TEXT) && (ctx->mode & RSA_CTX_MODE_PUBIN))
		print_text_pub_key(ctx, pub_out);
	if ((ctx->mode & RSA_CTX_MODE_TEXT) && !(ctx->mode & RSA_CTX_MODE_PUBIN))
		print_text_priv_key(ctx, priv_out);
	if (ctx->mode & RSA_CTX_MODE_MODULUS)
		print_modulus(ctx, ctx->mode & RSA_CTX_MODE_PUBOUT
			? pub_out->n : priv_out->n);
	if (!(ctx->mode & RSA_CTX_MODE_NOOUT) && (ctx->mode & RSA_CTX_MODE_PUBOUT))
		print_pub_key(ctx, pub_out);
	if (!(ctx->mode & RSA_CTX_MODE_NOOUT) && !(ctx->mode & RSA_CTX_MODE_PUBOUT))
		print_priv_key(ctx, priv_out);
}

void	append_text_int_with_new_line(char *out, __int128 num)
{
	char	arr[128];

	memset(arr, 0, sizeof(arr));
	int128toa(num, arr);
	strcat(arr, " (0x");
	int128tohex(num, &arr[0] + strlen(arr), "0123456789abcdef");
	strcat(arr, ")\n");
	strcat(out, arr);
}
