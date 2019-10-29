/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sha256_from_string.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:12:23 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/28 23:12:25 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include "ssl.h"
#include "utilities.h"
#include <string.h>

size_t			calculate_sha256_str_padding(const char *str, char **padded)
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
	(*padded)[len] = 0x80;
	(*padded)[padded_len - 4] = ((len * 8) >> 24) & 0b11111111;
	(*padded)[padded_len - 3] = ((len * 8) >> 16) & 0b11111111;
	(*padded)[padded_len - 2] = ((len * 8) >> 8) & 0b11111111;
	(*padded)[padded_len - 1] = ((len * 8) >> 0) & 0b11111111;
	return (padded_len);
}

t_hash_sha256	calculate_sha256_from_string(const char *str)
{
	t_hash_sha256		hash;
	char				*padded;
	char				*padded_cpy;
	size_t				padded_len;

	init_sha256_hash(&hash);
	padded_len = calculate_sha256_str_padding(str, &padded);
	padded_cpy = padded;
	while (padded_len)
	{
		calculate_sha256_block((t_reg32 *)padded, &hash);
		padded += 64;
		padded_len -= 64;
	}
	free(padded_cpy);
	return (hash);
}
