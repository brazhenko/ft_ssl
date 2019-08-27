int		init_hash_256(t_hash_sha256 *hash)
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