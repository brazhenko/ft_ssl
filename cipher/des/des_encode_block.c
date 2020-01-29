#include "des.h"
#include <string.h>
#include <stdatomic.h>
#include <utilities.h>

#include "s_permutation.c"

/*
** feistel()  function gets half of plain text block (32bit), final key
 * (48 bit) and "returns" the encoded block back to [t_deshalfblock res].
*/

int 		feistel(t_lpdeshalfblock hb, t_lpdes48key key, t_lpdeshalfblock res)
{
	t_desspreadhalfblock		shb;
	t_deshalfblock			hb2;

	des_permutation(*hb, shb, g_des_e_tbl,
			sizeof(g_des_e_tbl) / sizeof(g_des_e_tbl[0]));
	mem_xor(shb, key, shb, sizeof(shb));
	s_permutation(&shb, &hb2);
	des_permutation(hb2, hb2, g_des_p_tbl,
			sizeof(g_des_p_tbl) / sizeof(g_des_p_tbl[0]));
	memcpy(res, hb2, sizeof(hb2));
	return (0);
}

int 	des_round(t_lpdesblock block, t_lpdes48key key)
{
	t_deshalfblock		tmp;

	memset(&tmp, 0, sizeof(tmp));
	//
	feistel((t_lpdeshalfblock)((uint8_t *)block + 4), key, &tmp);
	mem_xor(tmp, block, tmp, sizeof(tmp));
	//
	memcpy(block, ((uint8_t*)block + 4), 4);
	memcpy(((uint8_t*)block + 4), &tmp, 4);
	return (0);
}
