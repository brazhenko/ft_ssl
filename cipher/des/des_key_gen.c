#include "des.h"
#include <string.h>

/*
**	[DES56KEY key] is spread into 2x28bit blocks
**  and they are rotted separately.
*/

# define CHARFIRSTBIT(c) ((c & (1u<<(CHAR_BIT-1u)))>>(CHAR_BIT-1u))
# define CHARLASTBIT(C) ((c) & 0b1U)

static int		rot_des56key_blocks_left(LPDES56KEY key)
{
	DES56KEY		tmp;

	tmp[0] = (*key)[0] << 1u;
	tmp[1] = (*key)[1] << 1u;
	tmp[2] = (*key)[2] << 1u;
	tmp[3] = (*key)[3] << 1u;
	tmp[4] = (*key)[4] << 1u;
	tmp[5] = (*key)[5] << 1u;
	tmp[6] = (*key)[6] << 1u;
	tmp[0] |= CHARFIRSTBIT(((*key)[1]));
	tmp[1] |= CHARFIRSTBIT(((*key)[2]));
	tmp[2] |= CHARFIRSTBIT(((*key)[3]));
	tmp[3] |= CHARFIRSTBIT(((*key)[4]));
	tmp[3] &= (UINT8_MAX - 0b10000u); // reset 012[3]4567 bit
	tmp[3] |= CHARFIRSTBIT((*key[0])) << 4u;
	tmp[4] |= CHARFIRSTBIT(((*key)[5]));
	tmp[5] |= CHARFIRSTBIT(((*key)[6]));
	tmp[6] |= (((*key)[3]) & 0b1000u) >> 3u;
	memcpy(key, tmp, sizeof(tmp));

	return (0);
}

int 			rot_des56key_blocks_left_n(LPDES56KEY key, uint8_t times)
{
	while (times)
	{
		rot_des56key_blocks_left(key);
		times--;
	}
	return (0);
}

static int		rot_des56key_blocks_right(LPDES56KEY key)
{
	DES56KEY		tmp;

	tmp[0] = (*key)[0] >> 1u;
	tmp[1] = (*key)[1] >> 1u;
	tmp[2] = (*key)[2] >> 1u;
	tmp[3] = (*key)[3] >> 1u;
	tmp[4] = (*key)[4] >> 1u;
	tmp[5] = (*key)[5] >> 1u;
	tmp[6] = (*key)[6] >> 1u;
	tmp[0] |= CHARFIRSTBIT(((*key)[1]));
	tmp[1] |= CHARFIRSTBIT(((*key)[2]));
	tmp[2] |= CHARFIRSTBIT(((*key)[3]));
	tmp[3] |= CHARFIRSTBIT(((*key)[4]));
	tmp[3] &= (UINT8_MAX - 0b10000u); // reset 012[3]4567 bit
	tmp[3] |= CHARFIRSTBIT((*key[0])) << 4u;
	tmp[4] |= CHARFIRSTBIT(((*key)[5]));
	tmp[5] |= CHARFIRSTBIT(((*key)[6]));
	tmp[6] |= (((*key)[3]) & 0b1000u) >> 3u;
	memcpy(key, tmp, sizeof(tmp));

	return (0);
}

int 			rot_des56key_blocks_right_n(LPDES56KEY key, uint8_t times)
{
	while (times)
	{
		rot_des56key_blocks_right(key);
		times--;
	}
	return (0);
}