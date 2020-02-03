/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_key_gen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:34:28 by a17641238         #+#    #+#             */
/*   Updated: 2020/01/30 17:34:28 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include <string.h>

/*
**	[t_des56key key] is spread into 2x28bit blocks
**  and they are rotted separately.
*/

static uint8_t	char_first_bit(uint8_t c)
{
	return ((c & (1u << (CHAR_BIT - 1u))) >> (CHAR_BIT - 1u));
}

static int		rot_des56key_blocks_left(t_lpdes56key key)
{
	t_des56key		tmp;

	tmp[0] = (*key)[0] << 1u;
	tmp[1] = (*key)[1] << 1u;
	tmp[2] = (*key)[2] << 1u;
	tmp[3] = (*key)[3] << 1u;
	tmp[4] = (*key)[4] << 1u;
	tmp[5] = (*key)[5] << 1u;
	tmp[6] = (*key)[6] << 1u;
	tmp[0] |= char_first_bit(((*key)[1]));
	tmp[1] |= char_first_bit(((*key)[2]));
	tmp[2] |= char_first_bit(((*key)[3]));
	tmp[3] |= char_first_bit(((*key)[4]));
	tmp[3] &= (UINT8_MAX - 0b10000u);
	tmp[3] |= char_first_bit((*key[0])) << 4u;
	tmp[4] |= char_first_bit(((*key)[5]));
	tmp[5] |= char_first_bit(((*key)[6]));
	tmp[6] |= (((*key)[3]) & 0b1000u) >> 3u;
	memcpy(key, tmp, sizeof(tmp));
	return (0);
}

int				rot_des56key_blocks_left_n(t_lpdes56key key, uint8_t times)
{
	while (times)
	{
		rot_des56key_blocks_left(key);
		times--;
	}
	return (0);
}

/*
** TODO rot right not working still
*/
