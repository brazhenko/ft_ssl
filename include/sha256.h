/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:03:00 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/28 23:03:01 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA256_H
# define FT_SHA256_H

# include <stdint.h>

/*
**	All macros defined below take 32-bit (8-byte) arguments and return
**	32-bit (8-byte) value.
*/

# define RSHIFT(x, n) (((x) >> (n)) | (((x) << (32 - (n)))))
# define RROT(x, n) ((x) >> (n))
# define SHA256_CH(x, y, z) (((x) & (y)) ^ ((~(x)) & (z)))
# define SHA256_MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

# define SHA256_S0(x) ((RSHIFT((x), 2)) ^ (RSHIFT((x), 13)) ^ (RSHIFT((x), 22)))
# define SHA256_S1(x) ((RSHIFT((x), 6)) ^ (RSHIFT((x), 11)) ^ (RSHIFT((x), 25)))
# define SHA256_S2(x) ((RSHIFT((x), 7)) ^ (RSHIFT((x), 18)) ^ (RROT((x), 3)))
# define SHA256_S3(x) ((RSHIFT((x), 17)) ^ (RSHIFT((x), 19)) ^ (RROT((x), 10)))

typedef uint32_t	t_reg32;

/*
**	Array of SHA-256 algorithm constants
*/

static const t_reg32 g_sha256_constants[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

typedef struct	s_hash_sha256
{
	t_reg32	hash[8];
	int		error;
}				t_hash_sha256;

void			*sha256(char *str, int flags);
int				init_sha256_hash(t_hash_sha256 *hash);
void			calculate_sha256_block(t_reg32 *ptr, t_hash_sha256 *hash);
t_hash_sha256	calculate_sha256_from_string(const char *str);
t_hash_sha256	calculate_sha256_from_file(const char *file_name);
t_hash_sha256	calculate_sha256_from_stdin(int flag_p);
void			print_sha256_hash(t_hash_sha256 hash, char *str, int flags);

#endif
