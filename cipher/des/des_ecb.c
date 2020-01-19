#include "des.h"
#include <stddef.h>
#include <stdio.h>
#include <utilities.h>
#include <md5.h>

int 		pbkdf_md5(t_cipher_context *ctx)
{
	char final_pass[2048];
	memset(final_pass, 0, sizeof(final_pass));
	strcpy(final_pass, ctx->password);
	memcpy(&final_pass[0] + strlen(final_pass), ctx->salt, sizeof(ctx->salt));
	// strncat(final_pass, ctx->salt);
	t_hash_md5 key;
	if (CPHR_ISSALTSET(ctx))
	{
		key = calculate_md5_from_mem(final_pass, strlen(ctx->password) + CIPHER_SALT_BYTE_LEN);
	}
	else
		key = calculate_md5_from_mem(final_pass, strlen(ctx->password));

	memcpy(ctx->key, &key, 16);
	return (0);
}


void		prepare_des_ecb_encrypt_key(t_cipher_context *ctx)
{
	if (CPHR_ISKEYSET(ctx))
		return ;
	if (!CPHR_ISPASSSET(ctx))
		set_cipher_password_from_stdin(ctx);
	if (!CPHR_ISSALTSET(ctx))
		set_cipher_random_pass_salt(ctx, DES_ECB_SALT_BYTE_LEN);

	if (CPHR_ISSALTSET(ctx))
	{
		write(ctx->output_fd, "Salted__", 8);
		write(ctx->output_fd, ctx->salt, sizeof(ctx->salt));
	}
	// generating key
	// ft_pbkdf(); ...
	pbkdf_md5(ctx);
}

void		prepare_des_ecb_decrypt_key(t_cipher_context *ctx)
{
	if (CPHR_ISKEYSET(ctx))
		return ;
	if (!CPHR_ISPASSSET(ctx))
		set_cipher_password_from_stdin(ctx);
	try_get_des_salt_from_fd(ctx);
	pbkdf_md5(ctx);
	// print_hex_memory(ctx->key, 8);
}

void		*des_ecb(t_cipher_context *ctx)
{
	if (CPHR_ISENCRYPTMODE(ctx))
	{
		prepare_des_ecb_encrypt_key(ctx);
		des_ecb_encrypt(ctx);
	}
	else if (CPHR_ISDECRYPTMODE(ctx))
	{
		prepare_des_ecb_decrypt_key(ctx);
		des_ecb_decrypt(ctx);
	}
	return (NULL);
}