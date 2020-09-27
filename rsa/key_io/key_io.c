//
// Created by 17641238 on 14.07.2020.
//

#include <utilities.h>
#include <string.h>
#include <rsa_context.h>
#include "base64.h"
#include "rsa.h"

/*
 * returns size of output byte string;
 */

union converter {
	__int128 data;
	unsigned char data2[16];
};

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

long append_int128_to_buff(unsigned char *dest, __int128 in)
{
	unsigned char buf[512];
	long ret;

	memset(buf, 0, sizeof(buf));
	ret = int128_to_asn(in, buf);
	memcpy(dest, buf, ret);
	return ret;
}

int 	rsa_private_der_out(const t_rsa_priv_key *in, unsigned char *out)
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

void	print_priv_key_formatted(int output_fd,
		char *base64_encoded_key);

int 	rsa_private_pem_out(t_rsa_context *ctx, const t_rsa_priv_key *in)
{
	unsigned char 	arr[2048];
	char 			arr2[2048];

	memset(arr, 0, sizeof(arr));
	memset(arr2, 0, sizeof(arr2));
	int total_size = rsa_private_der_out(in, arr);
	encode_base64_block_with_padding(arr, arr2, total_size);
	print_priv_key_formatted(ctx->output_fd, arr2);
	return (0);
}

int 	rsa_private_der_out_fd(t_rsa_context *ctx, const t_rsa_priv_key *in)
{
	unsigned char 	arr[2048];
	char 			arr2[2048];

	memset(arr, 0, sizeof(arr));
	memset(arr2, 0, sizeof(arr2));
	int total_size = rsa_private_der_out(in, arr);
	write(ctx->output_fd, arr, total_size);
	return (0);
}

int 	rsa_public_pem_out_fd(t_rsa_context *ctx, t_rsa_pub_key *in)
{
	char out[1024] = {0};
	unsigned char out3[1024] = {0};
	char out2[1024] = {0};
	int total_size = rsa_public_pem_out(in, out3);

	memset(out, 0, sizeof(out));
	encode_base64_block_with_padding(out3, out, total_size);

	strcat(out2, PUBLIC_KEY_HEADER);
	strcat(out2, out);
	strcat(out2, "\n");
	strcat(out2, PUBLIC_KEY_BOT);
	write(ctx->output_fd, out2, strlen(out2));
	return (0);
}

int 	rsa_public_der_out_fd(t_rsa_context *ctx, t_rsa_pub_key *in)
{
	char out[1024] = {0};
	unsigned char out3[1024] = {0};
	char out2[1024] = {0};
	int total_size = rsa_public_pem_out(in, out3);
	write(ctx->output_fd, out, total_size);
	return (0);
}

// https://stackoverflow.com/questions/55803033/rsa-public-key-bit-string-format


const char hardcode_header[] = "\x30\x0d\x06\x09\x2a\x86\x48\x86"
							   "\xf7\x0d\x01\x01\x01\x05\x00\x03";

int 	rsa_public_pem_out(t_rsa_pub_key *in, unsigned char *out)
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

int 	parse_asn_from_fd(int fd, t_rsa_priv_key *out)
{
	int		read_count;
	int 	tmp;
	unsigned char buf[2048];

	memset(buf, 0, sizeof(buf));
	read_count = 0;
	while ((tmp = read(fd, &buf[0] + read_count, 100)) > 0)
		read_count += tmp;
	asn_private_pem_in(buf, out);
	return (0);
}

int 	parse_pem_from_fd(int fd, t_rsa_priv_key *out)
{
	unsigned char bytes[1024] = {0};

	parse_asn_from_pem(fd, bytes);
	asn_private_pem_in(bytes, out);
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
		return (-1);
	if (read_count < strlen(PUBLIC_KEY_HEADER) + strlen(PUBLIC_KEY_BOT))
		return (-1);
	if (strncmp(buffer, PUBLIC_KEY_HEADER, strlen(PUBLIC_KEY_HEADER)) != 0)
		return (-1);
	if (strncmp(&buffer[0] + read_count - strlen(PUBLIC_KEY_BOT), PUBLIC_KEY_BOT, strlen(PUBLIC_KEY_BOT)) != 0)
		return (-1);
	memset(buffer2, 0, sizeof(buffer2));
	unsigned govno = read_count - strlen(PUBLIC_KEY_HEADER) - strlen(PUBLIC_KEY_BOT);
	memcpy(buffer2, &buffer[0] + strlen(PUBLIC_KEY_HEADER), govno);
	memset(buffer, 0, sizeof(buffer));
	base64_decode_block((uint8_t*)buffer2, (char*)out, govno);
	return 0;
}

int 	parse_pub_from_pem(int fd, t_rsa_pub_key *out)
{

	unsigned char buf[1024] = {0};
	parse_pub_der_from_pem_fd(fd, buf);
	const unsigned char size = buf[1];

	if (size == 0)
		return (-1);
	if (buf[0] != 0x30)
		return (-1);
	if (memcmp(buf + 2, hardcode_header, 16) != 0)
		return (-1);
	int i = 18 + 4;
	i += parse_int128_from_asn(buf, i, &out->n);
	i += parse_int128_from_asn(buf, i, &out->e);

	return (0);
}

int 	parse_pub_from_der(int fd, t_rsa_pub_key *out)
{
	int		read_count;
	int 	tmp;
	unsigned char 	buffer[2048];

	read_count = 0;
	memset(buffer, 0, sizeof(buffer));
	while ((tmp = read(fd, &buffer[0] + read_count, 100)) > 0)
		read_count += tmp;

	const unsigned char size = buffer[1];

	if (size == 0)
		return (-1);
	if (buffer[0] != 0x30)
		return (-1);
	if (memcmp(buffer + 2, hardcode_header, 16) != 0)
		return (-1);
	int i = 18 + 4;
	i += parse_int128_from_asn(buffer, i, &out->n);
	i += parse_int128_from_asn(buffer, i, &out->e);

	return (0);
}