#include "des.h"
#include <stddef.h>
#include <utilities.h>
#include "pbkdf.h"

void		prepare_des_ecb_encrypt_key(t_cipher_context *ctx)
{
	if (cphr_is_key_set(ctx))
		return ;
	if (!cphr_is_pass_set(ctx))
		set_cipher_password_from_stdin(ctx);
	if (!cphr_is_salt_set(ctx))
		set_cipher_random_pass_salt(ctx, DES_SALT_BYTE_LEN);
	if (cphr_is_salt_set(ctx))
	{
		write(ctx->output_fd, "Salted__", 8);
		write(ctx->output_fd, ctx->salt, DES_SALT_BYTE_LEN);
	}
	pbkdf_md5(ctx);
}

void		prepare_des_ecb_decrypt_key(t_cipher_context *ctx)
{
	if (cphr_is_key_set(ctx))
		return ;
	if (!cphr_is_pass_set(ctx))
		set_cipher_password_from_stdin(ctx);
	try_get_des_salt_from_fd(ctx);
	pbkdf_md5(ctx);
}

void		*des_ecb(t_cipher_context *ctx)
{
	if (cphr_is_encrypt_mode(ctx))
	{
		prepare_des_ecb_encrypt_key(ctx);
		des_ecb_encrypt(ctx);
	}
	else if (cphr_is_decrypt_mode(ctx))
	{
		prepare_des_ecb_decrypt_key(ctx);
		des_ecb_decrypt(ctx);
	}
	return (NULL);
}
