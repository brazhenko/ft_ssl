/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genrsa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:36:10 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/28 16:13:16 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cxxabi.h>
#include "rsa.h"
#include <string.h>
#include <genrsa_context.h>
#include <key_io.h>
#include "base64.h"
#include "utilities.h"

static uint64_t	generate_1st_prime()
{
	const int	fd = open("/dev/urandom", O_RDONLY);
	uint64_t	prime;

	if (fd < 0)
		fatal("generate_2nd_prime, cannot open random decice");
	prime = 1;
	while (!is_prime(prime) || !(prime >> 31U))
	{
		if (read(fd, &prime, 4) != 4) // HARDCODE
			fatal("generate_2nd_prime, cannot read from random device");
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
		fatal("generate_2nd_prime, cannot open random decice");
	prime = 1;
	while (!is_prime(prime) || !(prime >> 31U) || !((first_prime * prime) >> 63U))
	{
		if (read(fd, &prime, 4) != 4) // HARDCODE
			fatal("generate_2nd_prime, cannot read from random device");
		write(2, ".", 1);
	}
	write(2, "+\n", 2);
	close(fd);
	return prime;
}

void	generate_2_primes_for_key(t_rsa_priv_key *k)
{
	const uint64_t	p = generate_1st_prime();
	uint64_t		q;

	q = generate_2nd_prime(p);
	while (q == p)
		q = generate_2nd_prime(p);
	k->q = q;
	k->p = p;
}

/*
**	 generates 64-bit private key
*/

void	genrsa(int ac, char **av)
{
	t_genrsa_context	*ctx;
	t_rsa_priv_key		k;
	__int128			euler_func;

	ctx = parse_gen_rsa_argv(ac, av);
	nstrprint(1, "Generating RSA private key, 64 bit long modulus\n");
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
	delete_gen_rsa_ctx(ctx);
}
