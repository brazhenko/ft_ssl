#include <stddef.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

/*
** greatest common divisor algorithm
*/

static uint64_t gcd(uint64_t a, uint64_t b)
{
    while (a != b)
    {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    return (a);
}

/*
** n - number to test for primality
** k - precision
**
** ret in [0, 100]% 0=number is not prime, 100=number is prime
** ret (-1) if error
*/

//https://www.cyberforum.ru/cpp-beginners/thread847326.html

int miller_rabin_test(uint64_t n, int k)
{
	uint64_t a;
	const int fd = open("/dev/urandom", O_RDONLY);
	uint64_t s, t;
	uint64_t tmp;

	if (fd < 0)
		return (-1);
	if (n % 2 == 2 || n < 2)
		return (0);
	t = n - 1;
	s = 0;
	while (t % 2 == 0)
	{
		t /= 2;
		s++;
	}
    for (int i = 0; i < k; ++i)
    {
        if (read(fd, &a, sizeof(a)) != sizeof(a))
            return (-1);
        a = (a + 2) %  (n + 2) - 2;

    }

    return 100 - (int)((2^-k)*100);
}