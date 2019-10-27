#include "sha256.h"
#include "ssl.h"
#include "utilities.h"
#include <string.h>

/*
**      According to the fact that minimum addressable piece is BYTE not BIT we
**      use all parameters from sha256 documentation divided by 8.
*/

int				init_sha256_hash(t_hash_sha256 *hash)
{
	hash->hash[0] = 0x6a09e667;
	hash->hash[1] = 0xbb67ae85;
	hash->hash[2] = 0x3c6ef372;
	hash->hash[3] = 0xa54ff53a;
	hash->hash[4] = 0x510e527f;
	hash->hash[5] = 0x9b05688c;
	hash->hash[6] = 0x1f83d9ab;
	hash->hash[7] = 0x5be0cd19;
	hash->error = 0;
	return (0);
}

void			update_sha256_block(t_hash_sha256 *hash, reg32 *tmp)
{
	hash->hash[0] += tmp[0];
	hash->hash[1] += tmp[1];
	hash->hash[2] += tmp[2];
	hash->hash[3] += tmp[3];
	hash->hash[4] += tmp[4];
	hash->hash[5] += tmp[5];
	hash->hash[6] += tmp[6];
	hash->hash[7] += tmp[7];
}

static int		calculate_w_array(reg32* ptr, reg32 *w)
{
	size_t		i;

	i = 0;
	// TODO refactor this hardcode pizdec-------
	while (i < 16)
	{
		w[i] = 0;

		w[i] |= (ptr[i] >> 24) & 0b11111111;
		w[i] |= (((ptr[i] >> 16) & 0b11111111) << 8);
		w[i] |= (((ptr[i] >> 8) & 0b11111111) << 16);
		w[i] |= (((ptr[i] >> 0) & 0b11111111) << 24);
		i++;
	}
	while (i < 64)
	{
		w[i] = 	w[i - 16] +
				SHA256_S2(w[i - 15]) +
				w[i - 7] +
				SHA256_S3(w[i - 2]);
		i++;
	}
	return (0);
}

int				calculate_sha256_block(reg32 *ptr, t_hash_sha256 *hash)
{
	size_t		i;
	reg32		tmp[8];
	reg32		t1, t2;
	reg32		w[64];

	calculate_w_array(ptr, w);
	memcpy(tmp, hash->hash, 8 * sizeof(reg32));
	i = 0;
	while (i < 64)
	{
		t1 = tmp[7] + SHA256_S1(tmp[4]) + SHA256_CH(tmp[4], tmp[5], tmp[6]) +
				sha256_constants[i] + w[i];
		t2 = SHA256_S0(tmp[0]) + SHA256_MAJ(tmp[0], tmp[1], tmp[2]);
		tmp[7] = tmp[6];
		tmp[6] = tmp[5];
		tmp[5] = tmp[4];
		tmp[4] = tmp[3] + t1;
		tmp[3] = tmp[2];
		tmp[2] = tmp[1];
		tmp[1] = tmp[0];
		tmp[0] = t1 + t2;
		i++;
	}
	update_sha256_block(hash, tmp);
	return (0);
}

void			*sha256(char *str, int flags)
{
	t_hash_sha256	hash;

	if (flags & FLAG_P || flags & FLAG_STDIN)
		hash = calculate_sha256_from_stdin();
	else if (flags & FLAG_S)
		hash = calculate_sha256_from_string(str);
	else
		hash = calculate_sha256_from_file(str);

	print_sha256_hash(hash, str, flags);
	return (NULL);
}