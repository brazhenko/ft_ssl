//
// Created by 17641238 on 27.09.2020.
//

#include <rsa.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "internal_key_io.h"

int 	rsa_parse_priv_der(int input_fd, t_rsa_priv_key *out)
{
	int		read_count;
	int 	tmp;
	unsigned char buf[2048];

	memset(buf, 0, sizeof(buf));
	read_count = 0;
	while ((tmp = read(input_fd, &buf[0] + read_count, 100)) > 0)
		read_count += tmp;
	asn_private_pem_in(buf, out);
	return (0);
}

int 	rsa_parse_priv_pem(int input_fd, t_rsa_priv_key *out)
{
	unsigned char bytes[1024] = {0};
	int ret;

	ret = parse_asn_from_pem(input_fd, bytes);
	if (ret)
		return (1);
	ret = asn_private_pem_in(bytes, out);
	if (ret)
		return (1);
	return (0);
}

int 	rsa_parse_pub_der(int fd, t_rsa_pub_key *out)
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

int 	rsa_parse_pub_pem(int fd, t_rsa_pub_key *out)
{

	unsigned char buf[1024] = {0};
	parse_pub_der_from_pem_fd(fd, buf);
	const unsigned char size = buf[1];

	if (size == 0)
		return (1);
	if (buf[0] != 0x30)
		return (1);
	if (memcmp(buf + 2, hardcode_header, 16) != 0)
		return (1);
	int i = 18 + 4;
	i += parse_int128_from_asn(buf, i, &out->n);
	i += parse_int128_from_asn(buf, i, &out->e);

	return (0);
}
