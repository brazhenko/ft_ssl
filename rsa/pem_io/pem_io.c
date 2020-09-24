//
// Created by 17641238 on 14.07.2020.
//

#include <utilities.h>
#include <string.h>
#include "base64.h"
#include "rsa.h"

// original
// 303f 020100 020900ea2a3fa55a32c9fb 0203010001 020803b91c3deb010121 020500fcfd7a89 020500ecf36f63 020500e70d6171 020401b5cc13 020500e6f8cae1


// 30
//
// 3f - amount of bytes
//
// 01
// 00

// == N
// 02
// 09
// 00 ea 2a 3f a5 5a 32 c9 fb

// == E
// 02
// 03
// 010001

// == D
// 02
// 08
// 03b91c3deb010121

// == P
// 02
// 05
// 00fcfd7a89

// == Q
// 02
// 05
// 00ecf36f63

// == DP
// 02
// 05
// 00e70d6171

// == DQ
// 02
// 04
// 01b5cc13

// QINV
// 02
// 05
// 00e6f8cae1



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

int 	rsa_private_pem_out(const t_rsa_priv_key *in, unsigned char *memory)
{
	unsigned char total_size;

	total_size = 0;
	memory[0] = 0x30;
	memory[2] = 0x02;
	memory[3] = 0x01;
	memory[4] = 0x00;
	total_size += 5;
	total_size += append_int128_to_buff(&memory[0] + total_size, in->n);
	total_size += append_int128_to_buff(&memory[0] + total_size, in->e);
	total_size += append_int128_to_buff(&memory[0] + total_size, in->d);
	total_size += append_int128_to_buff(&memory[0] + total_size, in->p);
	total_size += append_int128_to_buff(&memory[0] + total_size, in->q);
	total_size += append_int128_to_buff(&memory[0] + total_size, in->dp);
	total_size += append_int128_to_buff(&memory[0] + total_size, in->dq);
	total_size += append_int128_to_buff(&memory[0] + total_size, in->qinv);
	memory[1] = total_size - 2;
	return total_size;
}

//30
//3e
//020100
//02090
//
//09f39bab9005b5599
//02030100010208656a11a0ec49b9f9020500b0f264ab020500e65c86cb02042721af410205009dd613220204334a9948
//=========================
//30
//24
//300d
//
//06
//09
//2a864886f70d010101
//
//05
//00
//
//0313003010
//
//02
//09
//009f39bab9005b5599 // N
//
//02
//03
//010001				// E

int 	rsa_private_pem_in(t_rsa_priv_key *out, const char *infile)
{
	return 0;
}