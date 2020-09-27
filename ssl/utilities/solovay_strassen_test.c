#include <stddef.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
** n - number to test for primarity
** k - precision
**
** ret in [0, 100]% 0=number is not prime, 100=number is prime
** ret (-1) if error
*/

//https://www.cyberforum.ru/cpp-beginners/thread847326.html

/*
**	makes a random number from interval [l, r]; l < r
*/

uint64_t	interval(uint64_t rand, uint64_t l, uint64_t r)
{
	uint64_t	ret;

	ret = rand % (r - l) + l;
	return ret;
}

uint64_t 	fast_mod_pow(uint64_t base, uint64_t pw, uint64_t mod)
{
	unsigned __int128	base2;
	unsigned __int128	mod2;
	unsigned __int128	result2;
	uint64_t	result;

	base2 = base;
	mod2 = mod;
	result2 = 1;
	while (pw > 0)
	{
		if (pw & 1U)
			result2 = (result2 * base2) % mod2;
		base2 = (base2 * base2) % mod2;
		pw >>= 1U;
	}
	result = result2;
	return result;
}

uint64_t 	mod_pow(uint64_t n, uint64_t pw, uint64_t mod)
{
	unsigned __int128	tmp;
	unsigned __int128	n2;
	unsigned __int128	mod2;
	uint64_t	ret;

	tmp = (unsigned  __int128)1;
	n2 = (unsigned  __int128)n;
	mod2 = (unsigned  __int128)mod;
	while (pw)
	{
		tmp *= n2;
		tmp %= mod2;
		pw--;
	}
	ret = (uint64_t)tmp;
	return ret;
}

int			miller_rabin_test(uint64_t n, int k)
{
	uint64_t a;
	static int fd = 0;
	uint64_t s, t;
	uint64_t	x;

	if (!fd)
		fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (-1);
	if (n == 2 || n == 3)
		return (100);
	if (n % 2 == 0 || n < 2)
		return (0);

	t = n - 1;
	s = 0;
	while (t % 2 == 0)
	{
		t /= 2;
		s++;
	}

	// k rounds
	while (k--)
	{
		if (read(fd, &a, sizeof(a)) != sizeof(a))
			return (-1);
		a = interval(a, 2, n-2);
		x = fast_mod_pow(a, t, n);
		if (x == 1 || x == n - 1)
			continue ;
		for (uint64_t j = 0; j + 1 < s; j++)
		{
			x = fast_mod_pow(x, 2, n);
			if (x == 1)
				return (0);
			if (x == n - 1)
				break ;
		}
		if (x == n - 1)
			continue ;
		return (0);
	}

    return 100 - (int)((1./fast_mod_pow(2, k, INT_MAX) * 100));
}

int			miller_rabin_test_fd(uint64_t n, int k, int fd)
{
	uint64_t a;
	uint64_t s, t;
	uint64_t	x;

	if (n == 2 || n == 3)
		return (100);
	if (n % 2 == 0 || n < 2)
		return (0);

	t = n - 1;
	s = 0;
	while (t % 2 == 0)
	{
		t /= 2;
		s++;
	}

	// k rounds
	while (k--)
	{
		if (read(fd, &a, sizeof(a)) != sizeof(a))
		{
			perror("cannot read random data");
			exit(EXIT_FAILURE);
		}
		a = interval(a, 2, n-2);
		x = fast_mod_pow(a, t, n);
		if (x == 1 || x == n - 1)
			continue ;
		for (uint64_t j = 0; j + 1 < s; j++)
		{
			x = fast_mod_pow(x, 2, n);
			if (x == 1)
				return (0);
			if (x == n - 1)
				break ;
		}
		if (x == n - 1)
			continue ;
		return (0);
	}

	return 100 - (int)((1./fast_mod_pow(2, k, INT_MAX)*100));
}

bool		is_prime(uint64_t num)
{
	const int 	fd = open("/dev/urandom", O_RDONLY);
	const int 	round_count = (int)ceil(log2(num));
	bool		ret;

	if (fd < 0)
	{
		perror("cannot open random device");
		exit(EXIT_FAILURE);
	}
	ret = miller_rabin_test_fd(num, round_count, fd) != 0;
	close(fd);
	return ret;
}