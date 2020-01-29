#include <md5.h>

int			pbkdf_md5(t_cipher_context *ctx)
{
	char			final_pass[2048];
	t_hash_md5		key;

	memset(final_pass, 0, sizeof(final_pass));
	strcpy(final_pass, ctx->password);
	memcpy(&final_pass[0] + strlen(final_pass), ctx->salt, sizeof(ctx->salt));
	if (cphr_is_salt_set(ctx))
	{
		key = calculate_md5_from_mem(final_pass, strlen(ctx->password)
				+ CIPHER_SALT_BYTE_LEN);
	}
	else
		key = calculate_md5_from_mem(final_pass, strlen(ctx->password));
	if (!cphr_is_key_set(ctx))
		memcpy(ctx->key, &key, 8);
	if (!cphr_is_iv_set(ctx))
		memcpy(ctx->vector_ini, (unsigned char *)&key + 8, 8);
	ctx->mode |= 0b10000;
	ctx->mode |= 0b10000000;
	return (0);
}
