#include "des.h"
#include <string.h>
#include <stdio.h>
#include <stdatomic.h>

int 	des_spread_half_block(LPDESHALFBLOCK hb, LPDESSPREADHALFBLOCK shb)
{
	uint8_t		i;
	uint8_t		t;

	i = 0;
	memset(shb, 0, sizeof(DESSPREADHALFBLOCK));
	while (i < sizeof(des_e_tbl))
	{
		t = des_e_tbl[i];
		(*shb)[i/8] |= (
				((*hb)[t / 8u] & ((1u) << (8u - t % 8u - 1))) ?
				(1u << (8u - i % 8u - 1)) : 0u
		);
		i++;
	}
	return (0);
}

// TODO not compress
int 	des_compress_half_block(LPDESHALFBLOCK shb)
{
	uint8_t			i;
	uint8_t			t;
	DESHALFBLOCK	tmp;

	i = 0;
//	puts("__before last permutation: ");
//	debug32(shb);
	while (i < sizeof(des_p_tbl))
	{
		t = des_p_tbl[i];
		tmp[i/8] |= (
				((*shb)[t / 8u] & ((1u) << (8u - t % 8u - 1))) ?
				(1u << (8u - i % 8u - 1)) : 0u
		);
		i++;
	}

//	puts("__after last permutation:");
//	debug32(&tmp);
	memcpy(shb, tmp, sizeof(tmp));
	return (0);
}

// TODO rename
int 	xor1(LPDESHALFBLOCK one, LPDESHALFBLOCK two, LPDESHALFBLOCK res)
{
	DESHALFBLOCK	tmp;

	tmp[0] = (*one)[0] ^ (*two)[0];
	tmp[1] = (*one)[1] ^ (*two)[1];
	tmp[2] = (*one)[2] ^ (*two)[2];
	tmp[3] = (*one)[3] ^ (*two)[3];
	memcpy(res, tmp, sizeof(tmp));
	return (0);
}

int 	xor2(LPDESSPREADHALFBLOCK shb, LPDES48KEY key, LPDESSPREADHALFBLOCK res)
{
	DESSPREADHALFBLOCK	tmp;

	tmp[0] = (*shb)[0] ^ (*key)[0];
	tmp[1] = (*shb)[1] ^ (*key)[1];
	tmp[2] = (*shb)[2] ^ (*key)[2];
	tmp[3] = (*shb)[3] ^ (*key)[3];
	tmp[4] = (*shb)[4] ^ (*key)[4];
	tmp[5] = (*shb)[5] ^ (*key)[5];
	memcpy(res, tmp, sizeof(tmp));
	return (0);
}

#define B0(c)	(((c)&(1u<<7u))>>7u)
#define B1(c)	(((c)&(1u<<6u))>>6u)
#define B2(c)	(((c)&(1u<<5u))>>5u)
#define B3(c)	(((c)&(1u<<4u))>>4u)
#define B4(c)	(((c)&(1u<<3u))>>3u)
#define B5(c)	(((c)&(1u<<2u))>>2u)
#define B6(c)	(((c)&(1u<<1u))>>1u)
#define B7(c)	(((c)&(1u<<0u))>>0u)
#define CB2(c1,c2) (((c1)<<1u) | c2)
#define CB4(c1,c2,c3,c4)(((c1)<<3u)|((c2)<<2u)|((c3)<<1u)|((c4)<<0u))

int 	sss(LPDESSPREADHALFBLOCK shb, LPDESHALFBLOCK hb)
{
	memset(hb, 0, sizeof(DESHALFBLOCK));
	(*hb)[0] |= s[0][CB2(B0((*shb)[0]), B5((*shb)[0]))]
	[CB4(B1((*shb)[0]), B2((*shb)[0]), B3((*shb)[0]), B4((*shb)[0]))] << 4u;
	(*hb)[0] |= s[1][CB2(B6((*shb)[0]), B3((*shb)[1]))]
	[CB4(B7((*shb)[0]), B0((*shb)[1]), B1((*shb)[1]), B2((*shb)[1]))];
	(*hb)[1] |= s[2][CB2(B4((*shb)[1]), B1((*shb)[2]))]
	[CB4(B5((*shb)[1]), B6((*shb)[1]), B7((*shb)[1]), B0((*shb)[2]))] << 4u;
	(*hb)[1] |= s[3][CB2(B2((*shb)[2]), B7((*shb)[2]))]
	[CB4(B3((*shb)[2]), B4((*shb)[2]), B5((*shb)[2]), B6((*shb)[2]))];
	(*hb)[2] |= s[4][CB2(B0((*shb)[3]), B5((*shb)[3]))]
	[CB4(B1((*shb)[3]), B2((*shb)[3]), B3((*shb)[3]), B4((*shb)[3]))] << 4u;
	(*hb)[2] |= s[5][CB2(B6((*shb)[3]), B3((*shb)[4]))]
	[CB4(B7((*shb)[3]), B0((*shb)[4]), B1((*shb)[4]), B2((*shb)[4]))];
	(*hb)[3] |= s[6][CB2(B4((*shb)[4]), B1((*shb)[5]))]
	[CB4(B5((*shb)[4]), B6((*shb)[4]), B7((*shb)[4]), B0((*shb)[5]))] << 4u;
	(*hb)[3] |= s[7][CB2(B2((*shb)[5]), B7((*shb)[5]))]
	[CB4(B3((*shb)[5]), B4((*shb)[5]), B5((*shb)[5]), B6((*shb)[5]))];

	return (0);
}

#undef B0
#undef B1
#undef B2
#undef B3
#undef B4
#undef B5
#undef B6
#undef B7
#undef CB2
#undef CB4

/*
** f1() Feistel functions gets [LPDESHALFBLOCK b], [LPDES48KEY key],
** [DESHALFBLOCK res].
** as arguments and "returns" the encoded block back to [DESHALFBLOCK res].
*/

int 	f1(LPDESHALFBLOCK hb, LPDES48KEY key, LPDESHALFBLOCK res)
{
	DESSPREADHALFBLOCK		shb;
	DESHALFBLOCK			hb2;

	des_spread_half_block(hb, &shb);

	xor2(&shb, key, &shb);

	sss(&shb, &hb2);

	des_compress_half_block(&hb2);

	memcpy(res, hb2, sizeof(hb2));
	return (0);
}

int 	des_encode_round(LPDESBLOCK block, LPDES48KEY key)
{
	DESHALFBLOCK		tmp;
	memset(&tmp, 0, sizeof(tmp));
	//
	f1((LPDESHALFBLOCK)((uint8_t*)block + 4), key, &tmp);
	xor1(&tmp, (LPDESHALFBLOCK)block, &tmp);
	//
	memcpy(block, ((uint8_t*)block + 4), 4);
	memcpy(((uint8_t*)block + 4), &tmp, 4);

	return (0);
}
