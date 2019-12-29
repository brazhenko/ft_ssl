#include "des.h"
#include <string.h>

int 	des_permute_key1(LPDES64KEY key)
{
	DES64KEY	res;
	uint8_t		i;
	uint8_t		t;
	i = 0;

	memset(res, 0, sizeof(res));
	while (i < 56)
	{
		t = cmprs_key[i];
		// i = 34 t = 30
		res[i/8] |= (
				((*key)[t / 8u] & ((1u)<<(8u - t % 8u - 1))) ?
				(1u << (8u - i % 8u - 1)) : 0u
		);

	//00000000 11111100 11011111 10010000 00100101 01010011 10101000 00110000
	//00000000 11111100 11011111 10010010 01010101 00111010 10000011
	//00000000 11111100 11011111 10010010 01010101 00111010 10000011 00001000

		i++;
	}
	memcpy(key, res, sizeof(res));
	return (0);
}