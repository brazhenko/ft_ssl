/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:36:42 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/29 19:24:06 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "rsa_context.h"
#include "rsa.h"
#include "utilities.h"
#include <unistd.h>
#include "key_io.h"
#include "internal_rsa.h"

#define STRING1	"RSA Private-Key: (64 bit)\n"
#define STRING2	"modulus: "
#define STRING3	"publicExponent: "
#define STRING4	"privateExponent: "
#define STRING5	"prime1: "
#define STRING6	"prime2: "
#define STRING7	"exponent1: "
#define STRING8	"exponent2: "
#define STRING9	"coefficient: "
#define STRING10	"Modulus="
#define STRING11	"Exponent: "
#define STRING12	"RSA Public-Key: (64 bit)\n"
#define STRING13	"Modulus: "

void	generate_out_key(t_rsa_context *ctx,
		t_rsa_pub_key *pub_out,
		t_rsa_priv_key *priv_out)
{
	if (!(ctx->mode & RSA_CTX_MODE_PUBIN))
	{
		pub_out->n = priv_out->n;
		pub_out->e = priv_out->e;
	}
}

void	print_modulus(t_rsa_context *ctx, __int128 modulus)
{
	char	out[128];

	memset(out, 0, sizeof(out));
	strcat(out, STRING10);
	int128tohex(modulus, &out[0] + strlen(out), "0123456789ABCDEF");
	strcat(out, "\n");
	write(ctx->output_fd, out, strlen(out));
}

void	print_text_pub_key(t_rsa_context *ctx, t_rsa_pub_key *k)
{
	char	to_print[2048];

	memset(to_print, 0, sizeof(to_print));
	strcat(to_print, STRING12);
	strcat(to_print, STRING13);
	append_text_int_with_new_line(to_print, k->n);
	strcat(to_print, STRING11);
	append_text_int_with_new_line(to_print, k->e);
	write(ctx->output_fd, to_print, strlen(to_print));
}

void	print_text_priv_key(t_rsa_context *ctx, t_rsa_priv_key *k)
{
	char	to_print[2048];

	memset(to_print, 0, sizeof(to_print));
	strcat(to_print, STRING1);
	strcat(to_print, STRING2);
	append_text_int_with_new_line(to_print, k->n);
	strcat(to_print, STRING3);
	append_text_int_with_new_line(to_print, k->e);
	strcat(to_print, STRING4);
	append_text_int_with_new_line(to_print, k->d);
	strcat(to_print, STRING5);
	append_text_int_with_new_line(to_print, k->p);
	strcat(to_print, STRING6);
	append_text_int_with_new_line(to_print, k->q);
	strcat(to_print, STRING7);
	append_text_int_with_new_line(to_print, k->dp);
	strcat(to_print, STRING8);
	append_text_int_with_new_line(to_print, k->dq);
	strcat(to_print, STRING9);
	append_text_int_with_new_line(to_print, k->qinv);
	write(ctx->output_fd, to_print, strlen(to_print));
}

void	rsa(int ac, char **av)
{
	t_rsa_context	*ctx;
	t_rsa_priv_key	priv_key;
	t_rsa_pub_key	pub_key;

	memset(&priv_key, 0, sizeof(priv_key));
	memset(&pub_key, 0, sizeof(pub_key));
	ctx = init_rsa_ctx();
	ctx = parse_rsa_argv(ac, av, ctx);
	parse_key(ctx, &pub_key, &priv_key);
	if (ctx->mode & RSA_CTX_MODE_PUBIN)
		ctx->mode |= RSA_CTX_MODE_PUBOUT;
	generate_out_key(ctx, &pub_key, &priv_key);
	process_output(ctx, &pub_key, &priv_key);
	delete_rsa_ctx(ctx);
}
