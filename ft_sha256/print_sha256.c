#include "ft_sha256.h"
#include <stdio.h>

void			print_sha256_hash(t_hash_sha256 hash)
{
	for (int i = 0; i < 8; i++)
	{
		// putchar(hex_arr[(hash.hash[i] >> 28) & 0b1111]);
		printf("%08x", hash.hash[i]);
	}
	printf("\n");
}

// hardcode
void			print_hx(reg32* hash)
{
	for (int i = 0; i < 8; i++)
	{
		printf("%08x ", hash[i]);
	}
	printf("\n");
}