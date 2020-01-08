#include "des.h"
#include <stdio.h>

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
	fflush(stdout);
	return 0;
}

