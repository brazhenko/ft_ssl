#include "des.h"
#include <stddef.h>
#include <utilities.h>
#include "pbkdf.h"

void		prepare_des_cbc_encrypt_key_iv(t_cipher_context *ctx)
{
	if (!cphr_is_key_set(ctx))
	{
		if (!cphr_is_pass_set(ctx))
			set_cipher_password_from_stdin(ctx);
		if (!cphr_is_salt_set(ctx))
			set_cipher_random_pass_salt(ctx, DES_SALT_BYTE_LEN);
		write(ctx->output_fd, "Salted__", 8);
		write(ctx->output_fd, ctx->salt, DES_SALT_BYTE_LEN);
		pbkdf_md5(ctx);
	}
	else
	{
		if (!cphr_is_iv_set(ctx))
		{
			nstrprinterror(1, "no iv set\n");
			exit(EXIT_FAILURE);
		}
	}
}

void		prepare_des_cbc_decrypt_key_iv(t_cipher_context *ctx)
{
	if (!cphr_is_key_set(ctx))
	{
		if (!cphr_is_pass_set(ctx))
			set_cipher_password_from_stdin(ctx);
		if (!cphr_is_salt_set(ctx))
			try_get_des_salt_from_fd(ctx);
		pbkdf_md5(ctx);
	}
	else
	{
		if (!cphr_is_iv_set(ctx))
		{
			nstrprinterror(1, "no iv set\n");
			exit(EXIT_FAILURE);
		}
	}
}

void		*des_cbc(t_cipher_context *ctx)
{
	if (cphr_is_encrypt_mode(ctx))
	{
		prepare_des_cbc_encrypt_key_iv(ctx);
		des_cbc_encrypt(ctx);
	}
	else if (cphr_is_decrypt_mode(ctx))
	{
		prepare_des_cbc_decrypt_key_iv(ctx);
		des_cbc_decrypt(ctx);
	}
	return (NULL);
}
