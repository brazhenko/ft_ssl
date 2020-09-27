//
// Created by 17641238 on 27.09.2020.
//

#ifndef FT_SSL_INTERNAL_KEY_IO_H
#define FT_SSL_INTERNAL_KEY_IO_H

#include <rsa.h>
#include <stddef.h>

// https://stackoverflow.com/questions/55803033/rsa-public-key-bit-string-format

int 	asn_private_pem_in(const unsigned char *arr, t_rsa_priv_key *out);
int		parse_asn_from_pem(int fd, unsigned char *out);
size_t	int128_to_asn(__int128 in, unsigned char *buf_out);
int 	parse_int128_from_asn(const unsigned char *buf, size_t idx, __int128 *out);
int 	parse_pub_der_from_pem_fd(int fd, unsigned char *out);
int 	rsa_priv_to_der_string(const t_rsa_priv_key *in, unsigned char *out);
int 	rsa_public_to_der_string(const t_rsa_pub_key *in, unsigned char *out);

union converter {
	__int128 data;
	unsigned char data2[16];
};

static const char hardcode_header[] = "\x30\x0d\x06\x09\x2a\x86\x48\x86"
									  "\xf7\x0d\x01\x01\x01\x05\x00\x03";

# define PRIVATE_KEY_HEADER	"-----BEGIN RSA PRIVATE KEY-----\n"
# define PRIVATE_KEY_BOT	"-----END RSA PRIVATE KEY-----\n"

# define PUBLIC_KEY_HEADER	"-----BEGIN PUBLIC KEY-----\n"
# define PUBLIC_KEY_BOT		"-----END PUBLIC KEY-----\n"

#endif //FT_SSL_INTERNAL_KEY_IO_H
