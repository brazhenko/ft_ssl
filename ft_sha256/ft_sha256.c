#include "ft_sha256.h"

int		init_sha256_hash(t_hash_sha256 *hash)
{
	hash->hash[0] = 0x6a09e667;
	hash->hash[1] = 0xbb67ae85;
	hash->hash[2] = 0x3c6ef372;
	hash->hash[3] = 0xa54ff53a;
	hash->hash[4] = 0x510e527f;
	hash->hash[5] = 0x9b05688c;
	hash->hash[6] = 0x1f83d9ab;
	hash->hash[7] = 0x5be0cd19;
	return (0);
}

int		calculate_sha256_block(void *ptr, t_hash_sha256* hash)
{
	size_t		i;
	reg32		tmp[8];
	reg32		T1, T2;

	// TODO fix hardcode below
	tmp[0] = hash->hash[0];
	tmp[1] = hash->hash[1];
	tmp[2] = hash->hash[2];
	tmp[3] = hash->hash[3];
	tmp[4] = hash->hash[4];
	tmp[5] = hash->hash[5];
	tmp[6] = hash->hash[6];
	tmp[7] = hash->hash[7];
	//-------

	i = 0;
	while (i < 64)
	{
		T1 = tmp[7] + SHA256_S1(tmp[4]) + \
		SHA256_CH(tmp[4], tmp[5], tmp[6]) + sha256_constants[i] /* + Wj */;
		T2 = SHA_256_S0(temp[0] + SHA256_MAJ(temp[0], temp[1], temp[2]));
		temp[7] = temp[6]; // h
		temp[6] = temp[5]; // g
		temp[5] = temp[4]; // f
		temp[4] = temp[3] + T1; // e
		temp[3] = temp[2]; // d
		temp[2] = temp[1]; // c
		temp[1] = temp[0]; // b
		temp[0] = T1 + T2; // a

		i++;
	}
	// TODO think how to optimise this increment
	hash->hash[0] += temp[0];
	hash->hash[1] += temp[1];
	hash->hash[2] += temp[2];
	hash->hash[3] += temp[3];
	hash->hash[4] += temp[4];
	hash->hash[5] += temp[5];
	hash->hash[6] += temp[6];
	hash->hash[7] += temp[7];
	// -------
}