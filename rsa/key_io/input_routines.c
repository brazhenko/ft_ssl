/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 19:28:57 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/29 19:31:22 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rsa.h>
#include <string.h>
#include <unistd.h>
#include "internal_key_io.h"

int		rsa_parse_priv_der(int input_fd, t_rsa_priv_key *out)
{
	int				read_count;
	int				tmp;
	unsigned char	buf[2048];

	memset(buf, 0, sizeof(buf));
	read_count = 0;
	while ((tmp = read(input_fd, &buf[0] + read_count, 100)) > 0)
		read_count += tmp;
	asn_private_pem_in(buf, out);
	return (0);
}

int		rsa_parse_priv_pem(int input_fd, t_rsa_priv_key *out)
{
	unsigned char	bytes[1024];
	int				ret;

	memset(bytes, 0, sizeof(bytes));
	ret = parse_asn_from_pem(input_fd, bytes);
	if (ret)
		return (1);
	ret = asn_private_pem_in(bytes, out);
	if (ret)
		return (1);
	return (0);
}

int		rsa_parse_pub_der(int fd, t_rsa_pub_key *out)
{
	int				read_count;
	int				tmp;
	unsigned char	buffer[2048];
	int				ret;
	unsigned char	size;

	read_count = 0;
	memset(buffer, 0, sizeof(buffer));
	while ((tmp = read(fd, &buffer[0] + read_count, 100)) > 0)
		read_count += tmp;
	size = buffer[1];
	if (size == 0)
		return (-1);
	if (buffer[0] != 0x30)
		return (-1);
	if (memcmp(buffer + 2, g_hardcode_header, 16) != 0)
		return (-1);
	tmp = 18 + 4;
	ret = parse_int128_from_asn(buffer, tmp, &out->n);
	if (ret == -1)
		return (1);
	tmp += ret;
	ret = parse_int128_from_asn(buffer, tmp, &out->e);
	return ((ret == -1) ? 1 : 0);
}

int		rsa_parse_pub_pem(int fd, t_rsa_pub_key *out)
{
	unsigned char			buf[1024];
	unsigned char			size;
	int						ret;
	int						i;

	memset(buf, 0, sizeof(buf));
	parse_pub_der_from_pem_fd(fd, buf);
	size = buf[1];
	if (size == 0)
		return (1);
	if (buf[0] != 0x30)
		return (1);
	if (memcmp(buf + 2, g_hardcode_header, 16) != 0)
		return (1);
	i = 18 + 4;
	ret = parse_int128_from_asn(buf, i, &out->n);
	if (ret == -1)
		return (1);
	i += ret;
	ret = parse_int128_from_asn(buf, i, &out->e);
	if (ret == -1)
		return (1);
	return (0);
}
