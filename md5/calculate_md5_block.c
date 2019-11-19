/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_md5_block.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:23:25 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/28 23:23:26 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static int		round1_md5(t_reg32 *tmp, t_reg32 *buffer)
{
	ROUND1(tmp[0], tmp[1], tmp[2], tmp[3], buffer[0], 7, 1);
	ROUND1(tmp[3], tmp[0], tmp[1], tmp[2], buffer[1], 12, 2);
	ROUND1(tmp[2], tmp[3], tmp[0], tmp[1], buffer[2], 17, 3);
	ROUND1(tmp[1], tmp[2], tmp[3], tmp[0], buffer[3], 22, 4);
	ROUND1(tmp[0], tmp[1], tmp[2], tmp[3], buffer[4], 7, 5);
	ROUND1(tmp[3], tmp[0], tmp[1], tmp[2], buffer[5], 12, 6);
	ROUND1(tmp[2], tmp[3], tmp[0], tmp[1], buffer[6], 17, 7);
	ROUND1(tmp[1], tmp[2], tmp[3], tmp[0], buffer[7], 22, 8);
	ROUND1(tmp[0], tmp[1], tmp[2], tmp[3], buffer[8], 7, 9);
	ROUND1(tmp[3], tmp[0], tmp[1], tmp[2], buffer[9], 12, 10);
	ROUND1(tmp[2], tmp[3], tmp[0], tmp[1], buffer[10], 17, 11);
	ROUND1(tmp[1], tmp[2], tmp[3], tmp[0], buffer[11], 22, 12);
	ROUND1(tmp[0], tmp[1], tmp[2], tmp[3], buffer[12], 7, 13);
	ROUND1(tmp[3], tmp[0], tmp[1], tmp[2], buffer[13], 12, 14);
	ROUND1(tmp[2], tmp[3], tmp[0], tmp[1], buffer[14], 17, 15);
	ROUND1(tmp[1], tmp[2], tmp[3], tmp[0], buffer[15], 22, 16);
	return (0);
}

static int		round2_md5(t_reg32 *tmp, t_reg32 *buffer)
{
	ROUND2(tmp[0], tmp[1], tmp[2], tmp[3], buffer[1], 5, 17);
	ROUND2(tmp[3], tmp[0], tmp[1], tmp[2], buffer[6], 9, 18);
	ROUND2(tmp[2], tmp[3], tmp[0], tmp[1], buffer[11], 14, 19);
	ROUND2(tmp[1], tmp[2], tmp[3], tmp[0], buffer[0], 20, 20);
	ROUND2(tmp[0], tmp[1], tmp[2], tmp[3], buffer[5], 5, 21);
	ROUND2(tmp[3], tmp[0], tmp[1], tmp[2], buffer[10], 9, 22);
	ROUND2(tmp[2], tmp[3], tmp[0], tmp[1], buffer[15], 14, 23);
	ROUND2(tmp[1], tmp[2], tmp[3], tmp[0], buffer[4], 20, 24);
	ROUND2(tmp[0], tmp[1], tmp[2], tmp[3], buffer[9], 5, 25);
	ROUND2(tmp[3], tmp[0], tmp[1], tmp[2], buffer[14], 9, 26);
	ROUND2(tmp[2], tmp[3], tmp[0], tmp[1], buffer[3], 14, 27);
	ROUND2(tmp[1], tmp[2], tmp[3], tmp[0], buffer[8], 20, 28);
	ROUND2(tmp[0], tmp[1], tmp[2], tmp[3], buffer[13], 5, 29);
	ROUND2(tmp[3], tmp[0], tmp[1], tmp[2], buffer[2], 9, 30);
	ROUND2(tmp[2], tmp[3], tmp[0], tmp[1], buffer[7], 14, 31);
	ROUND2(tmp[1], tmp[2], tmp[3], tmp[0], buffer[12], 20, 32);
	return (0);
}

static int		round3_md5(t_reg32 *tmp, t_reg32 *buffer)
{
	ROUND3(tmp[0], tmp[1], tmp[2], tmp[3], buffer[5], 4, 33);
	ROUND3(tmp[3], tmp[0], tmp[1], tmp[2], buffer[8], 11, 34);
	ROUND3(tmp[2], tmp[3], tmp[0], tmp[1], buffer[11], 16, 35);
	ROUND3(tmp[1], tmp[2], tmp[3], tmp[0], buffer[14], 23, 36);
	ROUND3(tmp[0], tmp[1], tmp[2], tmp[3], buffer[1], 4, 37);
	ROUND3(tmp[3], tmp[0], tmp[1], tmp[2], buffer[4], 11, 38);
	ROUND3(tmp[2], tmp[3], tmp[0], tmp[1], buffer[7], 16, 39);
	ROUND3(tmp[1], tmp[2], tmp[3], tmp[0], buffer[10], 23, 40);
	ROUND3(tmp[0], tmp[1], tmp[2], tmp[3], buffer[13], 4, 41);
	ROUND3(tmp[3], tmp[0], tmp[1], tmp[2], buffer[0], 11, 42);
	ROUND3(tmp[2], tmp[3], tmp[0], tmp[1], buffer[3], 16, 43);
	ROUND3(tmp[1], tmp[2], tmp[3], tmp[0], buffer[6], 23, 44);
	ROUND3(tmp[0], tmp[1], tmp[2], tmp[3], buffer[9], 4, 45);
	ROUND3(tmp[3], tmp[0], tmp[1], tmp[2], buffer[12], 11, 46);
	ROUND3(tmp[2], tmp[3], tmp[0], tmp[1], buffer[15], 16, 47);
	ROUND3(tmp[1], tmp[2], tmp[3], tmp[0], buffer[2], 23, 48);
	return (0);
}

static int		round4_md5(t_reg32 *tmp, t_reg32 *buffer)
{
	ROUND4(tmp[0], tmp[1], tmp[2], tmp[3], buffer[0], 6, 49);
	ROUND4(tmp[3], tmp[0], tmp[1], tmp[2], buffer[7], 10, 50);
	ROUND4(tmp[2], tmp[3], tmp[0], tmp[1], buffer[14], 15, 51);
	ROUND4(tmp[1], tmp[2], tmp[3], tmp[0], buffer[5], 21, 52);
	ROUND4(tmp[0], tmp[1], tmp[2], tmp[3], buffer[12], 6, 53);
	ROUND4(tmp[3], tmp[0], tmp[1], tmp[2], buffer[3], 10, 54);
	ROUND4(tmp[2], tmp[3], tmp[0], tmp[1], buffer[10], 15, 55);
	ROUND4(tmp[1], tmp[2], tmp[3], tmp[0], buffer[1], 21, 56);
	ROUND4(tmp[0], tmp[1], tmp[2], tmp[3], buffer[8], 6, 57);
	ROUND4(tmp[3], tmp[0], tmp[1], tmp[2], buffer[15], 10, 58);
	ROUND4(tmp[2], tmp[3], tmp[0], tmp[1], buffer[6], 15, 59);
	ROUND4(tmp[1], tmp[2], tmp[3], tmp[0], buffer[13], 21, 60);
	ROUND4(tmp[0], tmp[1], tmp[2], tmp[3], buffer[4], 6, 61);
	ROUND4(tmp[3], tmp[0], tmp[1], tmp[2], buffer[11], 10, 62);
	ROUND4(tmp[2], tmp[3], tmp[0], tmp[1], buffer[2], 15, 63);
	ROUND4(tmp[1], tmp[2], tmp[3], tmp[0], buffer[9], 21, 64);
	return (0);
}

int				calculate_md5_block(t_reg32 *ptr, t_hash_md5 *hash)
{
	t_reg32	tmp[4];

	tmp[0] = hash->a;
	tmp[1] = hash->b;
	tmp[2] = hash->c;
	tmp[3] = hash->d;
	round1_md5(tmp, ptr);
	round2_md5(tmp, ptr);
	round3_md5(tmp, ptr);
	round4_md5(tmp, ptr);
	hash->a += tmp[0];
	hash->b += tmp[1];
	hash->c += tmp[2];
	hash->d += tmp[3];
	return (0);
}
