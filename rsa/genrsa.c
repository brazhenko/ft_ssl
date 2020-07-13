#include <cxxabi.h>
#include "rsa.h"
#include "base64.h"
#include "utilities.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t generate_1()
{
	const int	fd = open("/dev/urandom", O_RDONLY);
	uint64_t	ret;

	if (fd < 0)
	{
		perror(__FUNCTION__);
		exit(EXIT_FAILURE);
	}
	if (read(fd, &ret, sizeof(ret)) != sizeof(ret))
	{
		perror(__FUNCTION__);
		exit(EXIT_FAILURE);
	}
	close(fd);
	return ret;
}

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
		if (read(fd, &prime, sizeof(prime)) != sizeof(prime))
		{
			perror(__FUNCTION__);
			exit(EXIT_FAILURE);
		}
		write(1, ".", 1);
	}
	write(1, "+\n", 2);
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
	printf("debug primes p: %llu, q: %llu\n", p, q);
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


/*
**	 generates 64 private key
*/

void	genrsa(int ac, char **av)
{
	__int128 euler_func;
	t_rsa_priv_key	k;

	memset(&k, 0, sizeof(k));
	generate_2_primes_for_key(&k);
	k.modulus_n = k.p * k.q;
	k.public_exponent_e = DEFAULT_PUBLIC_EXP;
	euler_func = (k.p - 1) * (k.q - 1);




}

//https://crypto.stackexchange.com/questions/21102/what-is-the-ssl-private-key-file-format

// 30
// 3e // bytecount!

// 02 01b Type[00] // RSA 2 primes
// 02 09b N[00c91e44827012371d]
// 02 03b E[010001]
// 02 08b D[6745377fa9c621b1]
// 02 05b P[00eb4c25fb]
// 02 05b Q[00dad043c7]
// 02 05b D mod (P-1) [00af938fd7]
// 02 04b D mod (Q-1) [0544c27d]
// 02 04b §[46b87a0e]



// 30 24 30 0d 06092a864886f70d01010105000313003010 0209 [00d635fd3f98395ab5] 0203 [010001]