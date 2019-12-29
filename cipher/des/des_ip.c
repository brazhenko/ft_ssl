#include "des.h"
#include <string.h>
#include <stdio.h>

int 	des_ip_forward(LPDESBLOCK block)
{
	DESBLOCK	res;
	uint8_t		i;
	uint8_t		t;
	i = 0;

	memset(res, 0, sizeof(res));
	while (i < DES_CIPHER_BIT_LEN)
	{
		t = des_shfl_tbl[i];

		res[i/8] |= (
				((*block)[t / 8] & ((1u)<<(8u - t % 8u - 1))) ?
				(1u << (8u - i % 8u - 1)) : 0u
				);
		i++;
	}
	memcpy(block, res, sizeof(res));
	return (0);
}

int 	des_ip_reverse(LPDESBLOCK block)
{
	DESBLOCK	res;
	uint8_t		i;
	uint8_t		t;
	i = 0;

	memset(res, 0, sizeof(res));
	while (i < DES_CIPHER_BIT_LEN)
	{
		t = des_shfl_tbl_r[i];

		res[i/8] |= (
				((*block)[t / 8] & ((1u)<<(8u - t % 8u - 1))) ?
				(1u << (8u - i % 8u - 1)) : 0u
		);
		i++;
	}
	memcpy(block, res, sizeof(res));
	return (0);
}

int 	des_ip_debug(LPDESBLOCK block)
{
	printf("0        ");
	printf("1        ");
	printf("2        ");
	printf("3        ");
	printf("4        ");
	printf("5        ");
	printf("6        ");
	printf("7        \n");

	printf("01234567 ");
	printf("01234567 ");
	printf("01234567 ");
	printf("01234567 ");
	printf("01234567 ");
	printf("01234567 ");
	printf("01234567 ");
	printf("01234567\n");
	for (int i = 0; i < 8; ++i)
	{
		printf("%d%d%d%d%d%d%d%d ",
				(*block)[i]&0b10000000 ? 1: 0,
				(*block)[i]&0b1000000 ? 1: 0,
				(*block)[i]&0b100000 ? 1: 0,
				(*block)[i]&0b10000 ? 1: 0,
				(*block)[i]&0b1000 ? 1: 0,
				(*block)[i]&0b100 ? 1: 0,
				(*block)[i]&0b10 ? 1: 0,
				(*block)[i]&0b1 ? 1: 0
		);
	}
	printf("\n\n");
	return 0;
}

