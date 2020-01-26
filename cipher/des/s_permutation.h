#ifndef S_PERMUTATION_H
# define S_PERMUTATION_H

#include "des.h"
#include <string.h>
#include <stdatomic.h>
#include <utilities.h>

/*
 * s_permutation() gets spread by des_e_tbl half block permutes and compresses
 * it to normal block.
 */

static uint8_t		t0(uint8_t c)
{
	return ((((c) & (1u<<7u))>>7u));
}

static uint8_t		t1(uint8_t c)
{
	return (((c)&(1u<<6u))>>6u);
}

static uint8_t		t2(uint8_t c)
{
	return (((c)&(1u<<5u))>>5u);
}

static uint8_t		t3(uint8_t c)
{
	return (((c)&(1u<<4u))>>4u);
}

static uint8_t		t4(uint8_t c)
{
	return (((c)&(1u<<3u))>>3u);
}

static uint8_t		t5(uint8_t c)
{
	return (((c)&(1u<<2u))>>2u);
}

static uint8_t		t6(uint8_t c)
{
	return (((c)&(1u<<1u))>>1u);
}

static uint8_t		t7(uint8_t c)
{
	return (((c)&(1u<<0u))>>0u);
}

static uint8_t 		cb2(uint8_t c1, uint8_t c2)
{
	return (((c1) << 1u) | c2);
}

static uint8_t 		cb4(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4)
{
	return (((c1)<<3u)|((c2)<<2u)|((c3)<<1u)|((c4)<<0u));
}

static int 	s_permutation(t_lpdesspreadhalfblock shb, t_lpdeshalfblock hb)
{
	memset(hb, 0, sizeof(t_deshalfblock));
	(*hb)[0] |= s[0][cb2(t0((*shb)[0]), t5((*shb)[0]))]
	[cb4(t1((*shb)[0]), t2((*shb)[0]), t3((*shb)[0]), t4((*shb)[0]))] << 4u;
	(*hb)[0] |= s[1][cb2(t6((*shb)[0]), t3((*shb)[1]))]
	[cb4(t7((*shb)[0]), t0((*shb)[1]), t1((*shb)[1]), t2((*shb)[1]))];
	(*hb)[1] |= s[2][cb2(t4((*shb)[1]), t1((*shb)[2]))]
	[cb4(t5((*shb)[1]), t6((*shb)[1]), t7((*shb)[1]), t0((*shb)[2]))] << 4u;
	(*hb)[1] |= s[3][cb2(t2((*shb)[2]), t7((*shb)[2]))]
	[cb4(t3((*shb)[2]), t4((*shb)[2]), t5((*shb)[2]), t6((*shb)[2]))];
	(*hb)[2] |= s[4][cb2(t0((*shb)[3]), t5((*shb)[3]))]
	[cb4(t1((*shb)[3]), t2((*shb)[3]), t3((*shb)[3]), t4((*shb)[3]))] << 4u;
	(*hb)[2] |= s[5][cb2(t6((*shb)[3]), t3((*shb)[4]))]
	[cb4(t7((*shb)[3]), t0((*shb)[4]), t1((*shb)[4]), t2((*shb)[4]))];
	(*hb)[3] |= s[6][cb2(t4((*shb)[4]), t1((*shb)[5]))]
	[cb4(t5((*shb)[4]), t6((*shb)[4]), t7((*shb)[4]), t0((*shb)[5]))] << 4u;
	(*hb)[3] |= s[7][cb2(t2((*shb)[5]), t7((*shb)[5]))]
	[cb4(t3((*shb)[5]), t4((*shb)[5]), t5((*shb)[5]), t6((*shb)[5]))];
	return (0);
}

#endif