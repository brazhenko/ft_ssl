/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:36:03 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/28 15:36:03 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_key_io.h"
#include <string.h>

long append_int128_to_buff(unsigned char *dest, __int128 in)
{
	unsigned char buf[512];
	long ret;

	memset(buf, 0, sizeof(buf));
	ret = int128_to_asn(in, buf);
	memcpy(dest, buf, ret);
	return ret;
}

int 	rsa_priv_to_der_string(const t_rsa_priv_key *in, unsigned char *out)
{
	unsigned char total_size;

	total_size = 0;
	out[0] = 0x30;
	out[2] = 0x02;
	out[3] = 0x01;
	out[4] = 0x00;
	total_size += 5;
	total_size += append_int128_to_buff(&out[0] + total_size, in->n);
	total_size += append_int128_to_buff(&out[0] + total_size, in->e);
	total_size += append_int128_to_buff(&out[0] + total_size, in->d);
	total_size += append_int128_to_buff(&out[0] + total_size, in->p);
	total_size += append_int128_to_buff(&out[0] + total_size, in->q);
	total_size += append_int128_to_buff(&out[0] + total_size, in->dp);
	total_size += append_int128_to_buff(&out[0] + total_size, in->dq);
	total_size += append_int128_to_buff(&out[0] + total_size, in->qinv);
	out[1] = total_size - 2;
	return total_size;
}

int 	rsa_public_to_der_string(const t_rsa_pub_key *in, unsigned char *out)
{

	unsigned char total_size;
	unsigned char pub_key_size;
	unsigned char tmp;

	total_size = 0;
	pub_key_size = 0;

	out[0] = 0x30;
	memcpy(&out[0] + 2, hardcode_header, sizeof(hardcode_header));
	total_size += (sizeof(hardcode_header) + 2 - 1);
	total_size += 4;
	tmp = append_int128_to_buff(&out[0] + total_size, in->n);
	total_size += tmp;
	pub_key_size += tmp;
	tmp = append_int128_to_buff(&out[0] + total_size, in->e);
	total_size += tmp;
	pub_key_size += tmp;

	out[1] = total_size - 2;
	out[18] = pub_key_size + 3;
	out[20] = 0x30;
	out[21] = pub_key_size;
	return (total_size);
}

int 	parse_int128_from_asn(const unsigned char *buf, size_t idx, __int128 *out)
{
	union converter cvt;

	cvt.data = 0;
	if (buf[idx] != 0x2)
		return (-1);
	for (int i = 0; i < buf[idx + 1]; i++)
		cvt.data2[buf[idx + 1] - i - 1] = buf[idx + 2 + i];
	*out = cvt.data;
	return (buf[idx + 1] + 2);
}
