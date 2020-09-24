//
// Created by 17641238 on 14.07.2020.
//

#include <utilities.h>
#include <string.h>
#include "base64.h"
#include "rsa.h"

// original
// 303f 020100 020900ea2a3fa55a32c9fb 0203010001 020803b91c3deb010121 020500fcfd7a89 020500ecf36f63 020500e70d6171 020401b5cc13 020500e6f8cae1

/*
 * returns size of output byte string;
 */

size_t	int128_to_asn(__int128 in, unsigned char *buf_out)
{
	union {
		__int128 data;
		unsigned char data2[16];
	} cvt;
	unsigned char *buf_out_copy_to_begin;
	char byte_count;

	buf_out_copy_to_begin = buf_out;
	cvt.data = in;
	byte_count = 15;
	while (byte_count > -1 && !cvt.data2[byte_count])
		byte_count--;
	if (0x7F < cvt.data2[byte_count])
		byte_count++;
	buf_out[0] = 0x02;
	buf_out[1] = byte_count + 1;
	buf_out += 2;
	while (byte_count > -1)
	{
		*buf_out = cvt.data2[byte_count];
		buf_out++;
		byte_count--;
	}
	*buf_out = '\0';
	return (buf_out - buf_out_copy_to_begin);
}

long append_int128_to_buff(unsigned char *dest, __int128 in)
{
	unsigned char buf[512];
	long ret;

	memset(buf, 0, sizeof(buf));
	ret = int128_to_asn(in, buf);
	memcpy(dest, buf, ret);
	return ret;
}

int 	rsa_private_pem_out(const t_rsa_priv_key *in, unsigned char *out)
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

// 3024300d06092a864886f70d01010105000313003010020900a617108445f357750203010001
// 3024300d06092a864886f70d01010105000313003010020900a617108445f357750203010001

// https://stackoverflow.com/questions/55803033/rsa-public-key-bit-string-format

int 	rsa_public_pem_out(t_rsa_pub_key *in, unsigned char *out)
{
	const char arr[] = "\x30\x0d\x06\x09\x2a\x86\x48\x86"
					   "\xf7\x0d\x01\x01\x01\x05\x00\x03";
	unsigned char total_size;
	unsigned char pub_key_size;
	unsigned char tmp;

	total_size = 0;
	pub_key_size = 0;

	out[0] = 0x30;
	memcpy(&out[0] + 2, arr, sizeof(arr));
	total_size += (sizeof(arr) + 2 - 1);
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

int 	rsa_private_pem_in(t_rsa_priv_key *out, const char *infile)
{
	return 0;
}