#include <cxxabi.h>
#include "rsa.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <genrsa_context.h>
#include "base64.h"
#include "utilities.h"

static uint64_t	generate_1_prime()
{
	const int	fd = open("/dev/urandom", O_RDONLY);
	uint64_t	prime;

	if (fd < 0)
	{
		perror(__FUNCTION__);
		exit(EXIT_FAILURE);
	}
	prime = 1;
	while (!is_prime(prime))
	{
		if (read(fd, &prime, 4) != 4) // HARDCODE
		{
			perror(__FUNCTION__);
			exit(EXIT_FAILURE);
		}
		write(2, ".", 1);
	}
	write(2, "+\n", 2);
	close(fd);
	return prime;
}

void	generate_2_primes_for_key(t_rsa_priv_key *k)
{
	const uint64_t	p = generate_1_prime();
	uint64_t		q;

	q = generate_1_prime();
	while (q == p)
		q = generate_1_prime();
	k->q = q;
		k->p = p;
}

/*
 * An implementation of extended Euclidean algorithm for RSA.
 * Returns integer x, y and gcd(a, b) for Bezout equation:
 * ax + by = gcd(a, b), gcd(a, b) is 1 for rsa.
 */

void	bezout(__int128 a, __int128 b, __int128 *xout, __int128 *yout)
{
	__int128 q,
	x=1, xx=0,
	y=0, yy=1;
	__int128 tmp;

	while (b)
	{
		q = a / b;
		tmp = a;
		a = b;
		b = tmp % b;
		tmp = x;
		x = xx;
		xx = tmp - xx*q;
		tmp = y;
		y = yy;
		yy = tmp - yy * q;
	}
	*xout = x;
	*yout = y;
}

void xgcd(__int128 *result, __int128 a, __int128 b)
{
	__int128 aa[2] = {1, 0}, bb[2] = {0, 1}, q;
	while (1)
	{
		q = a / b;
		a = a % b;
		aa[0] = aa[0] - q * aa[1];
		bb[0] = bb[0] - q * bb[1];
		if (a == 0)
		{
			result[0] = b;
			result[1] = aa[1];
			result[2] = bb[1];
			return;
		}
		q = b / a;
		b = b % a;
		aa[1] = aa[1] - q * aa[0];
		bb[1] = bb[1] - q * bb[0];
		if (b == 0)
		{
			result[0] = a;
			result[1] = aa[0];
			result[2] = bb[0];
			return;
		}
	}
}


// Returns modulo inverse of a with respect
// to m using extended Euclid Algorithm
// Assumption: a and m are coprimes, i.e.,
// gcd(a, m) = 1
__int128 mod_inverse(__int128 a, __int128 m)
{
	__int128 m0 = m;
	__int128 y = 0, x = 1;

	if (m == 1)
		return 0;
	while (a > 1)
	{
		// q is quotient
		__int128 q = a / m;
		__int128 t = m;
		// m is remainder now, process same as
		// Euclid's algo
		m = a % m, a = t;
		t = y;
		// Update y and x
		y = x - q * y;
		x = t;
	}
	// Make x positive
	if (x < 0)
		x += m0;
	return x;
}

/*
**	 generates 64-bit private key
*/

void	print_priv_key_formatted(const t_genrsa_context *ctx,
		char *base64_encoded_key)
{
	const unsigned len = strlen(base64_encoded_key);
	char out[1024];
	unsigned i;

	memset(out, 0, sizeof(out));
	strcat(out, PRIVATE_KEY_HEADER);
	i=0;
	while (i < len)
	{
		strncat(out, base64_encoded_key + i, 64);
		strcat(out, "\n");
		i += 64;
	}
	strcat(out, PRIVATE_KEY_BOT);
	write(ctx->output_fd, out, strlen(out));
}

void	genrsa(int ac, char **av)
{
	const t_genrsa_context	*ctx = parse_gen_rsa_argv(ac, av);
	t_rsa_priv_key	k;
	__int128	euler_func;
	unsigned char memory[1024] = {0};
	char out[1024] = {0};
	int total_size;

	memset(&k, 0, sizeof(k));
	k.e = DEFAULT_PUBLIC_EXP;
	generate_2_primes_for_key(&k);
	k.n = k.p * k.q;
	euler_func = (k.p - 1) * (k.q - 1);
	k.d = mod_inverse(k.e, euler_func);
	k.dp = k.d % k.p;
	k.dq = k.d % k.q;
	k.qinv = mod_inverse(k.q, k.p);
	nstrprinterror(1, "e is 65537 (0x10001)\n");
	total_size = rsa_private_pem_out(&k, memory);
	encode_base64_block_with_padding(memory, out, total_size);
	print_priv_key_formatted(ctx, out);
	delete_gen_rsa_ctx((t_genrsa_context*)ctx);

	//////////////// generating public key by private key for tests.
	int			output_fd = open("key.pub", O_CREAT | O_WRONLY | O_TRUNC, 0666);

	t_rsa_pub_key pk;
	memset(&pk, 0, sizeof(pk));
	pk.e = k.e;
	pk.n = k.n;
	unsigned char arr3[1024] = {0};
	total_size = rsa_public_pem_out(&pk, arr3);

	memset(out, 0, sizeof(out));
	encode_base64_block_with_padding(arr3, out, total_size);

	write(output_fd, PUBLIC_KEY_HEADER, sizeof(PUBLIC_KEY_HEADER) - 1);
	write(output_fd, out, strlen(out));
	write(output_fd, "\n", 1);
	write(output_fd, PUBLIC_KEY_BOT, sizeof(PUBLIC_KEY_BOT) - 1);

}
