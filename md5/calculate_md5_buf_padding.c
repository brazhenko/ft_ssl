/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_md5_buf_padding.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 23:02:13 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/29 23:02:14 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

size_t	calculate_md5_buf_padding(char *padded, size_t len)
{
	size_t		pd_len;
	size_t		ret;
	size_t		lst_b;

	pd_len = len + 1;
	ret = 0;
	padded[len % (BUFLEN)] = 0x80;
	if ((pd_len % 64 == 0) || (pd_len % 64 > 56))
		ret = 64 + (64 - len % 64);
	else
		ret = 64 - len % 64;
	pd_len = ret + len;
	if (BUFLEN - 8 <= len % (BUFLEN) && len % (BUFLEN) < BUFLEN)
		lst_b = pd_len % (BUFLEN + 64) ? pd_len % (BUFLEN + 64) : (BUFLEN + 64);
	else
		lst_b = pd_len % (BUFLEN) ? pd_len % (BUFLEN) : BUFLEN;
	padded[lst_b - 8] = (len * 8) >> (8 * 0) & A;
	padded[lst_b - 7] = (len * 8) >> (8 * 1) & A;
	padded[lst_b - 6] = (len * 8) >> (8 * 2) & A;
	padded[lst_b - 5] = (len * 8) >> (8 * 3) & A;
	padded[lst_b - 4] = (len * 8) >> (8 * 4) & A;
	padded[lst_b - 3] = (len * 8) >> (8 * 5) & A;
	padded[lst_b - 2] = (len * 8) >> (8 * 6) & A;
	padded[lst_b - 1] = (len * 8) >> (8 * 7) & A;
	return (ret);
}
