#include "des.h"
#include <string.h>
#include <stdatomic.h>

/*
** s_permutation() gets spread by des_e_tbl half block permutes and compresses
** it to normal block.
*/

static uint8_t	t(uint8_t c, uint8_t rot)
{
	return ((((c) & (1u << rot)) >> rot));
}

static uint8_t	cb2(uint8_t c1, uint8_t c2)
{
	return (((c1) << 1u) | c2);
}

static uint8_t	cb4(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4)
{
	return ((c1 << 3U) | ((c2) << 2u) | ((c3) << 1u) | ((c4) << 0u));
}

int				s_permutation(t_lpdesspreadhalfblock shb, t_lpdeshalfblock hb)
{
	memset(hb, 0, sizeof(t_deshalfblock));
	(*hb)[0] |= g_s[0][cb2(t((*shb)[0], 7), t((*shb)[0], 2))]
	[cb4(t((*shb)[0], 6), t((*shb)[0], 5), t((*shb)[0], 4), t((*shb)[0], 3))]
	<< 4u;
	(*hb)[0] |= g_s[1][cb2(t((*shb)[0], 1), t((*shb)[1], 4))]
	[cb4(t((*shb)[0], 0), t((*shb)[1], 7), t((*shb)[1], 6), t((*shb)[1], 5))];
	(*hb)[1] |= g_s[2][cb2(t((*shb)[1], 3), t((*shb)[2], 6))]
	[cb4(t((*shb)[1], 2), t((*shb)[1], 1), t((*shb)[1], 0), t((*shb)[2], 7))]
	<< 4u;
	(*hb)[1] |= g_s[3][cb2(t((*shb)[2], 5), t((*shb)[2], 0))]
	[cb4(t((*shb)[2], 4), t((*shb)[2], 3), t((*shb)[2], 2), t((*shb)[2], 1))];
	(*hb)[2] |= g_s[4][cb2(t((*shb)[3], 7), t((*shb)[3], 2))]
	[cb4(t((*shb)[3], 6), t((*shb)[3], 5), t((*shb)[3], 4), t((*shb)[3], 3))]
	<< 4u;
	(*hb)[2] |= g_s[5][cb2(t((*shb)[3], 1), t((*shb)[4], 4))]
	[cb4(t((*shb)[3], 0), t((*shb)[4], 7), t((*shb)[4], 6), t((*shb)[4], 5))];
	(*hb)[3] |= g_s[6][cb2(t((*shb)[4], 3), t((*shb)[5], 6))]
	[cb4(t((*shb)[4], 2), t((*shb)[4], 1), t((*shb)[4], 0), t((*shb)[5], 7))]
	<< 4u;
	(*hb)[3] |= g_s[7][cb2(t((*shb)[5], 5), t((*shb)[5], 0))]
	[cb4(t((*shb)[5], 4), t((*shb)[5], 3), t((*shb)[5], 2), t((*shb)[5], 1))];
	return (0);
}
