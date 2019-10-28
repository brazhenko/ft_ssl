/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_md5_from_string.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:23:14 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/28 23:23:15 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

size_t			calculate_md5_str_padding(const char *str, char **padded)
{
	size_t		len;
	size_t		padded_len;

	len = strlen(str);
	padded_len = len + 1;
	if (padded_len % 64 < 60)
	{
		padded_len = padded_len + (64 - padded_len % 64);
	}
	else
	{
		padded_len = padded_len + 64 + (64 - padded_len % 64);
	}
	*padded = (char *)malloc(padded_len);
	bzero(*padded, padded_len);
	memcpy(*padded, str, len);
	// TODO recode this hardcode
	(*padded)[len] = 0x80;
	(*padded)[padded_len - 8] = (len * 8) >> (8 * 0) & A;
	(*padded)[padded_len - 7] = (len * 8) >> (8 * 1) & A;
	(*padded)[padded_len - 6] = (len * 8) >> (8 * 2) & A;
	(*padded)[padded_len - 5] = (len * 8) >> (8 * 3) & A;
	(*padded)[padded_len - 4] = (len * 8) >> (8 * 4) & A;
	(*padded)[padded_len - 3] = (len * 8) >> (8 * 5) & A;
	(*padded)[padded_len - 2] = (len * 8) >> (8 * 6) & A;
	(*padded)[padded_len - 1] = (len * 8) >> (8 * 7) & A;
	return (padded_len);
}

t_hash_md5			calculate_md5_from_string(const char *str)
{
	t_hash_md5			hash;
	char				*padded;
	size_t				padded_len;

	init_md5_hash(&hash);
	padded_len = calculate_md5_str_padding(str, &padded);
	while (padded_len)
	{
		calculate_md5_block((reg32 *)padded, &hash);
		padded += 64;
		padded_len -= 64;
	}
	return (hash);
}
