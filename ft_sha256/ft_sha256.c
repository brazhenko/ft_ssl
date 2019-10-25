#include "ft_sha256.h"
#include "ft_ssl.h"
#include "utilities.h"
#include <string.h>

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
	return (0);
}


// TODO make honest hex printing
void			print_sha256_hash(t_hash_sha256 hash)
{
	for (int i = 0; i < 8; i++)
	{
// 	    putchar(hex_arr[(hash.hash[i] >> 28) & 0b1111]);
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

int				calculate_sha256_block(reg32 *ptr, t_hash_sha256 *hash)
{
	size_t		i;
	reg32		tmp[8];
	reg32		t1, t2;


	//---------
	reg32		w[64];
	for (int i = 0 ;i < 16; i++)
	{
		w[i] = 0;
		// TODO refactor this hardcode pizdec
		w[i] |=  (ptr[i] >> 24) & 0b11111111;
		w[i] |=  (((ptr[i] >> 16) & 0b11111111) << 8);
		w[i] |=  (((ptr[i] >> 8) & 0b11111111) << 16);
		w[i] |=  (((ptr[i] >> 0) & 0b11111111) << 24);
	}
	for (int i = 16; i < 64; i++)
	{
		w[i] = 	w[i - 16] +
		        SHA256_S2(w[i - 15]) +
		        w[i - 7] +
		        SHA256_S3(w[i - 2]);
	}
	//---------

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
		// Swapping elements
		t1 = 	tmp[7] +
				SHA256_S1(tmp[4]) +
				SHA256_CH(tmp[4], tmp[5], tmp[6]) +
				sha256_constants[i] +
				w[i];

		t2 = SHA256_S0(tmp[0]) + SHA256_MAJ(tmp[0], tmp[1], tmp[2]);
		tmp[7] = tmp[6]; // h
		tmp[6] = tmp[5]; // g
		tmp[5] = tmp[4]; // f
		tmp[4] = tmp[3] + t1; // e
		tmp[3] = tmp[2]; // d
		tmp[2] = tmp[1]; // c
		tmp[1] = tmp[0]; // b
		tmp[0] = t1 + t2; // a
		i++;
	}

	// TODO think how to optimise this increment
	hash->hash[0] += tmp[0];
	hash->hash[1] += tmp[1];
	hash->hash[2] += tmp[2];
	hash->hash[3] += tmp[3];
	hash->hash[4] += tmp[4];
	hash->hash[5] += tmp[5];
	hash->hash[6] += tmp[6];
	hash->hash[7] += tmp[7];
	// -------

	return (0);
}

// --------------------------

/*
**      According to the fact that minimum addressable piece is BYTE not BIT we
**      user all parameters from sha documentation divided by 8.
*/

size_t				calculate_sha256_padding(const char *str, char	**padded)
{
	size_t		len;
	size_t		mul8len;
	size_t		padded_len;

	len = strlen(str);
	padded_len = len + 1;
	padded_len = padded_len + ((padded_len % 64) ? (64 - padded_len % 64) : 64);
	*padded = (char *)malloc(padded_len);
	bzero(*padded, padded_len);
	memcpy(*padded, str, len);
	(*padded)[len] = 0x80;
	(*padded)[padded_len - 4] = ((len * 8) >> 24) & 0b11111111;
	(*padded)[padded_len - 3] = ((len * 8) >> 16) & 0b11111111;
	(*padded)[padded_len - 2] = ((len * 8) >> 8) & 0b11111111;
	(*padded)[padded_len - 1] = ((len * 8) >> 0) & 0b11111111;
	// printf("padded string len: %lu\norig len: %lu\n", padded_len, len);
	return (padded_len);
}

t_hash_sha256	calculate_sha256_from_string(const char *str)
{
	t_hash_sha256		hash;
	char				*padded;
	size_t				padded_len;

	init_sha256_hash(&hash);
	padded_len = calculate_sha256_padding(str, &padded);
	while (padded_len)
	{
		calculate_sha256_block((reg32 *)padded, &hash);
		padded += 64;
		padded_len -= 64;
	}
	return (hash);
}
// --------------------------

t_hash_sha256	calculate_sha256_from_file(const char *file_name)
{
	t_hash_sha256		hash;

	init_sha256_hash(&hash);

	return (hash);
}

t_hash_sha256	calculate_sha256_from_stdin(void)
{
	t_hash_sha256		hash;

	init_sha256_hash(&hash);

	return (hash);
}

void			*sha256(char *str, int flags)
{
	t_hash_sha256	hash;
	init_sha256_hash(&hash);

	if (flags & FLAG_P || flags & FLAG_STDIN)
	{
		hash = calculate_sha256_from_stdin();
		print_sha256_hash(hash);
	}
	else if (flags & FLAG_S)
	{
		hash = calculate_sha256_from_string(str);
		print_sha256_hash(hash);
	}
	else
	{
		hash = calculate_sha256_from_file(str);
		print_sha256_hash(hash);
	}
	return (NULL);
}