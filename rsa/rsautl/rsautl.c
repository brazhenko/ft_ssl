/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsautl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:36:47 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/29 19:13:11 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utilities.h>
#include <rsa.h>
#include <string.h>
#include "rsautl_context.h"
#include "key_io.h"
#include <unistd.h>
#include "internal_rsautl.h"

void		take_and_decrypt(t_rsautl_context *ctx,
							__int128 privexp,
							__int128 modulo)
{
	int					tmp;
	union u_encryptor	enc;

	enc.numero = 0;
	while ((tmp = read(ctx->input_fd, enc.arr, 8)) > 0)
	{
		if (tmp != 8)
			fatal("File was corrupted");
		enc.numero = fast_mod_pow(enc.numero, privexp, modulo);
		if (write(ctx->output_fd, enc.arr, len_till_pad(enc.arr))
					!= len_till_pad(enc.arr))
			fatal("Error on writing to file");
		enc.numero = 0;
	}
	if (tmp < 0)
		fatal("Error with out file");
}

void		rsautl_decrypt(t_rsautl_context *ctx)
{
	t_rsa_priv_key		priv_key;

	memset(&priv_key, 0, sizeof(priv_key));
	if (ctx->mode & RSAUTL_CTX_PUBIN)
		fatal("Need private key for this.");
	if (rsa_parse_priv_pem(ctx->inkey_fd, &priv_key) == 1)
		fatal("Error with input private key.");
	take_and_decrypt(ctx, priv_key.d, priv_key.n);
}

void		encrypt_end_put(t_rsautl_context *ctx,
					__int128 pubexp, __int128 modulo)
{
	uint64_t			cryptogramm;
	int					tmp;
	union u_encryptor	enc;

	enc.numero = 0;
	while ((tmp = read(ctx->input_fd, enc.arr, 7)) > 0)
	{
		memset(&enc.arr[0] + tmp, 0xff, 7 - tmp);
		cryptogramm = fast_mod_pow(enc.numero, pubexp, modulo);
		if (write(ctx->output_fd, &cryptogramm, sizeof(cryptogramm))
					!= sizeof(cryptogramm))
			fatal("Error on writing to file");
		enc.numero = 0;
	}
	if (tmp < 0)
		fatal("Error with out file");
}

void		rsautl_encrypt(t_rsautl_context *ctx)
{
	t_rsa_priv_key	priv_key;
	t_rsa_pub_key	pub_key;
	__int128		pubexp;
	__int128		modulo;

	memset(&priv_key, 0, sizeof(priv_key));
	memset(&pub_key, 0, sizeof(pub_key));
	if (ctx->mode & RSAUTL_CTX_PUBIN)
	{
		if (rsa_parse_pub_pem(ctx->inkey_fd, &pub_key) == 1)
			fatal("Error with input public key.");
		pubexp = pub_key.e;
		modulo = pub_key.n;
	}
	else
	{
		if (rsa_parse_priv_pem(ctx->inkey_fd, &priv_key) == 1)
			fatal("Error with input private key.");
		pubexp = priv_key.e;
		modulo = priv_key.n;
	}
	encrypt_end_put(ctx, pubexp, modulo);
}

void		rsautl(int ac, char **av)
{
	t_rsautl_context		*ctx;

	ctx = init_rsautl_ctx();
	ctx = parse_rsautl_argv(ac, av, ctx);
	if (ctx->mode & RSAUTL_CTX_DECRYPT)
		rsautl_decrypt(ctx);
	else
		rsautl_encrypt(ctx);
}
