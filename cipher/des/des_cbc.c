#include "des.h"
#include <stddef.h>
#include <stdio.h>
#include <utilities.h>
#include "pbkdf.h"
#include "des.h"

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
			puts("no iv");
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
			puts("no iv");
			exit(EXIT_FAILURE);
		}
	}

}

void		*des_cbc(t_cipher_context *ctx)
{
	if (cphr_is_encrypt_mode(ctx))
	{
		prepare_des_cbc_encrypt_key_iv(ctx);
//			puts("SALT");
//			print_hex_memory(ctx->salt, 8);
//			puts("KEY");
//			print_hex_memory(ctx->key, 8);
//			puts("IV");
//			print_hex_memory(ctx->vector_ini, 8);
		des_cbc_encrypt(ctx);
	}
	else if (cphr_is_decrypt_mode(ctx))
	{
		prepare_des_cbc_decrypt_key_iv(ctx);
//			puts("SALT");
//			print_hex_memory(ctx->salt, 8);
//			puts("KEY");
//			print_hex_memory(ctx->key, 8);
//			puts("IV");
//			print_hex_memory(ctx->vector_ini, 8);
		des_cbc_decrypt(ctx);
	}

	return (NULL);
}