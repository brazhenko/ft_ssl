#include "des.h"
#include <stddef.h>
#include <stdio.h>
#include <utilities.h>
#include <md5.h>

void		*des_ecb(t_cipher_context *ctx)
{
	if (!CPHR_ISKEYSET(ctx))
	{
		if (!CPHR_ISPASSSET(ctx))
			set_cipher_password_from_stdin(ctx);
		if (!CPHR_ISSALTSET(ctx))
			set_cipher_random_pass_salt(ctx, DES_ECB_SALT_BYTE_LEN);

		// generating key
		// ft_pbkdf(); ...
		// TODO fix key hardcode.
		{
			char final_pass[2048];
			memset(final_pass, 0, sizeof(final_pass));
			strcpy(final_pass, ctx->password);
			strcat(final_pass, ctx->salt);
			t_hash_md5 key;
			if (CPHR_ISSALTSET(ctx))
			{
				key = calculate_md5_from_mem(final_pass, strlen(ctx->password) + CIPHER_SALT_BYTE_LEN);
				write(2, ctx->password, strlen(ctx->password));
				write(2, ctx->salt, CIPHER_SALT_BYTE_LEN);
				write(ctx->output_fd, "Salted__", 8);
				write(ctx->output_fd, ctx->salt, sizeof(ctx->salt));
			}
			else
				key = calculate_md5_from_mem(final_pass, strlen(ctx->password));

			memcpy(ctx->key, &key, 16);
		}
		// ------------

	}
	write(ctx->output_fd, "\n______________\n", sizeof("\n______________\n"));
	print_hex_memory(ctx->salt, 8);
	print_hex_memory(ctx->key, 8);
	write(ctx->output_fd, "\n______________\n", sizeof("\n______________\n"));
	if (CPHR_ISENCODEMODE(ctx))
		des_ecb_encode(ctx);
	else if (CPHR_ISDECODEMODE(ctx))
		des_ecb_decode(ctx);
	return (NULL);
}