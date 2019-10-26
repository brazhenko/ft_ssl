#include "ft_sha256.h"
#include "ft_sha256.h"
#include "ft_ssl.h"
#include "utilities.h"
#include <string.h>

size_t			calculate_sha256_str_padding(const char *str, char	**padded)
{
	size_t		len;
	size_t		padded_len;

	len = strlen(str);
	padded_len = len + 1;

	if (padded_len % 64 < 60)
	{
		padded_len = padded_len + (64 - padded_len % 64);
	}
	else
	{
		padded_len = padded_len + 64 + (64 - padded_len % 64);
	}

	*padded = (char *)malloc(padded_len);
	bzero(*padded, padded_len);
	memcpy(*padded, str, len);
	(*padded)[len] = 0x80;
	(*padded)[padded_len - 4] = ((len * 8) >> 24) & 0b11111111;
	(*padded)[padded_len - 3] = ((len * 8) >> 16) & 0b11111111;
	(*padded)[padded_len - 2] = ((len * 8) >> 8) & 0b11111111;
	(*padded)[padded_len - 1] = ((len * 8) >> 0) & 0b11111111;
	return (padded_len);
}

t_hash_sha256	calculate_sha256_from_string(const char *str)
{
	t_hash_sha256		hash;
	char				*padded;
	size_t				padded_len;

	init_sha256_hash(&hash);
	padded_len = calculate_sha256_str_padding(str, &padded);
	while (padded_len)
	{
		calculate_sha256_block((reg32 *)padded, &hash);
		padded += 64;
		padded_len -= 64;
	}
	return (hash);
}
