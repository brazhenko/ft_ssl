/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsautl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:36:47 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/28 15:36:47 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utilities.h>
#include <printf.h>
#include <rsa.h>
#include <string.h>
#include "rsautl_context.h"
#include "key_io.h"
#include <unistd.h>

union encryptor
{
	unsigned __int128	numero;
	unsigned char 		arr[16];
};

void 	rsautl_decrypt(t_rsautl_context *ctx)
{
	t_rsa_priv_key 	priv_key;
	int 			tmp;
	union encryptor enc;

	enc.numero = 0;
	memset(&priv_key, 0, sizeof(priv_key));
	__int128 privexp;
	__int128 modulo;

	if (ctx->mode & RSAUTL_CTX_PUBIN)
		fatal("Need private key for this.");
	else
	{
		if (rsa_parse_priv_pem(ctx->inkey_fd, &priv_key) == 1)
			fatal("Error with input private key.");
		privexp = priv_key.d;
		modulo = priv_key.n;
	}
	while ((tmp = read(ctx->input_fd, enc.arr, 8)) > 0)
	{
		uint64_t plain = fast_mod_pow(enc.numero, privexp, modulo);
		if (write(ctx->output_fd, &plain, 7) != 7)
			fatal("Error on writing to file");
		enc.numero = 0;
	}
	if (tmp < 0)
		fatal("Error with out file");

}

void 	rsautl_encrypt(t_rsautl_context *ctx)
{
	t_rsa_priv_key 	priv_key;
	t_rsa_pub_key 	pub_key;
	int 			tmp;
	union encryptor enc;

	enc.numero = 0;
	memset(&priv_key, 0, sizeof(priv_key));
	memset(&pub_key, 0, sizeof(pub_key));
	__int128 pubexp;
	__int128 modulo;

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
	while ((tmp = read(ctx->input_fd, enc.arr, 7)) > 0)
	{
		uint64_t cryptogramm = fast_mod_pow(enc.numero, pubexp, modulo);
		printf("cryptogram: %llu\n", cryptogramm);
		if (write(ctx->output_fd, &cryptogramm, sizeof(cryptogramm)) != sizeof(cryptogramm))
			fatal("Error on writing to file");
		enc.numero = 0;
	}
	if (tmp < 0)
		fatal("Error with out file");


}

void	rsautl(int ac, char **av)
{
	t_rsautl_context		*ctx;

	ctx = init_rsautl_ctx();
	ctx = parse_rsautl_argv(ac, av, ctx);

	if (ctx->mode & RSAUTL_CTX_DECRYPT)
		rsautl_decrypt(ctx);
	else
		rsautl_encrypt(ctx);
}