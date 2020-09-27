#include <cxxabi.h>
#include "rsa.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <genrsa_context.h>
#include <key_io.h>
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
	while (!is_prime(prime) || !(prime >> 31U))
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

static uint64_t	generate_2nd_prime(uint64_t first_prime)
{
	const int	fd = open("/dev/urandom", O_RDONLY);
	uint64_t	prime;

	if (fd < 0)
	{
		perror(__FUNCTION__);
		exit(EXIT_FAILURE);
	}
	prime = 1;
	while (!is_prime(prime) || !(prime >> 31U) || !((first_prime * prime) >> 63U))
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

	q = generate_2nd_prime(p);
	while (q == p)
		q = generate_2nd_prime(p);
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

void	genrsa(int ac, char **av)
{
	const t_genrsa_context	*ctx = parse_gen_rsa_argv(ac, av);
	t_rsa_priv_key	k;
	__int128	euler_func;

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
	rsa_put_priv_pem(ctx->output_fd, &k);
	delete_gen_rsa_ctx((t_genrsa_context*)ctx);
}
