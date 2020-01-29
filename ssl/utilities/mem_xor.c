#include <stddef.h>

/*
** mem_xor() gets left, right, out mem pointers and len of
** bytes need to be XOR'ed. mem pointers could me equal
*/

void			*mem_xor(void *left, void *right, void *out, size_t len)
{
	unsigned char	*ptrleft;
	unsigned char	*ptrright;
	unsigned char	*ptrout;
	size_t			i;

	ptrleft = (unsigned char *)left;
	ptrright = (unsigned char *)right;
	ptrout = (unsigned char *)out;
	i = 0;
	while (i < len)
	{
		ptrout[i] = ptrleft[i] ^ ptrright[i];
		i++;
	}
	return (out);
}
