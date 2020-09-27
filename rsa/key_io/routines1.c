//
// Created by 17641238 on 27.09.2020.
//

#include <string.h>
#include <unistd.h>
#include "internal_key_io.h"
#include "base64.h"

int		parse_asn_from_pem(int fd, unsigned char *out)
{
	int		read_count;
	int 	tmp;
	char 	buffer[2048];
	char 	buffer2[2048];

	read_count = 0;
	memset(buffer, 0, sizeof(buffer));
	while ((tmp = read(fd, &buffer[0] + read_count, 100)) > 0)
		read_count += tmp;
	if (tmp < 0)
		return (-1);
	if (read_count < strlen(PRIVATE_KEY_HEADER) + strlen(PRIVATE_KEY_BOT))
		return (-1);
	if (strncmp(buffer, PRIVATE_KEY_HEADER, strlen(PRIVATE_KEY_HEADER)) != 0)
		return (-1);
	if (strncmp(&buffer[0] + read_count - strlen(PRIVATE_KEY_BOT), PRIVATE_KEY_BOT, strlen(PRIVATE_KEY_BOT)) != 0)
		return (-1);
	memset(buffer2, 0, sizeof(buffer2));
	unsigned govno = read_count - strlen(PRIVATE_KEY_HEADER) - strlen(PRIVATE_KEY_BOT);
	memcpy(buffer2, &buffer[0] + strlen(PRIVATE_KEY_HEADER), govno);
	memset(buffer, 0, sizeof(buffer));
	base64_decode_block((uint8_t*)buffer2, (char*)out, govno);
	return 0;
}

int 	asn_private_pem_in(const unsigned char *arr, t_rsa_priv_key *out)
{
	unsigned char 	buffer[1024];
	unsigned char total_size;
	unsigned char i;

	memset(buffer, 0, sizeof(buffer));
	if (arr[0] != 0x30)
		return (-1);
	if (!(total_size = arr[1]))
		return (-1);
	memcpy(buffer, arr, total_size);
	i = 5;
	i += parse_int128_from_asn(buffer, i, &out->n);
	i += parse_int128_from_asn(buffer, i, &out->e);
	i += parse_int128_from_asn(buffer, i, &out->d);
	i += parse_int128_from_asn(buffer, i, &out->p);
	i += parse_int128_from_asn(buffer, i, &out->q);
	i += parse_int128_from_asn(buffer, i, &out->dp);
	i += parse_int128_from_asn(buffer, i, &out->dq);
	i += parse_int128_from_asn(buffer, i, &out->qinv);
	return (0);
}

int 	parse_pub_der_from_pem_fd(int fd, unsigned char *out)
{
	int		read_count;
	int 	tmp;
	char 	buffer[2048];
	char 	buffer2[2048];

	read_count = 0;
	memset(buffer, 0, sizeof(buffer));
	while ((tmp = read(fd, &buffer[0] + read_count, 100)) > 0)
		read_count += tmp;
	if (tmp < 0)
		return (1);
	if (read_count < strlen(PUBLIC_KEY_HEADER) + strlen(PUBLIC_KEY_BOT))
		return (1);
	if (strncmp(buffer, PUBLIC_KEY_HEADER, strlen(PUBLIC_KEY_HEADER)) != 0)
		return (1);
	if (strncmp(&buffer[0] + read_count - strlen(PUBLIC_KEY_BOT), PUBLIC_KEY_BOT, strlen(PUBLIC_KEY_BOT)) != 0)
		return (1);
	memset(buffer2, 0, sizeof(buffer2));
	unsigned govno = read_count - strlen(PUBLIC_KEY_HEADER) - strlen(PUBLIC_KEY_BOT);
	memcpy(buffer2, &buffer[0] + strlen(PUBLIC_KEY_HEADER), govno);
	memset(buffer, 0, sizeof(buffer));
	base64_decode_block((uint8_t*)buffer2, (char*)out, govno);
	return 0;
}

size_t	int128_to_asn(__int128 in, unsigned char *buf_out)
{
	union converter cvt;
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
