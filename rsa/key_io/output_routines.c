//
// Created by 17641238 on 27.09.2020.
//

#include <unistd.h>
#include <string.h>
#include <rsa.h>
#include "internal_key_io.h"
#include "base64.h"

int 	rsa_put_priv_der(int output_fd, const t_rsa_priv_key *in)
{
	unsigned char 	arr[2048];
	char 			arr2[2048];

	memset(arr, 0, sizeof(arr));
	memset(arr2, 0, sizeof(arr2));
	int total_size = rsa_priv_to_der_string(in, arr);
	write(output_fd, arr, total_size);
	return (0);
}

int	print_priv_pem_key_formatted(int output_fd,
		char *base64_encoded_key)
{
	const unsigned len = strlen(base64_encoded_key);
	char out[1024];
	unsigned i;

	memset(out, 0, sizeof(out));
	strcat(out, PRIVATE_KEY_HEADER);
	i=0;
	while (i < len)
	{
		strncat(out, base64_encoded_key + i, 64);
		strcat(out, "\n");
		i += 64;
	}
	strcat(out, PRIVATE_KEY_BOT);
	i = strlen(out);
	if ((write(output_fd, out, i) == i))
		return (0);
	return (1);
}

int 	rsa_put_priv_pem(int output_fd, const t_rsa_priv_key *in)
{
	unsigned char 	arr[2048];
	char 			arr2[2048];

	memset(arr, 0, sizeof(arr));
	memset(arr2, 0, sizeof(arr2));
	int total_size = rsa_priv_to_der_string(in, arr);
	encode_base64_block_with_padding(arr, arr2, total_size);
	return print_priv_pem_key_formatted(output_fd, arr2);
}

int 	rsa_put_pub_der(int output_fd, const t_rsa_pub_key *in)
{
	unsigned char result[1024];

	memset(result, 0, sizeof(result));
	int total_size = rsa_public_to_der_string(in, result);
	write(output_fd, result, total_size);
	return (0);
}

int 	rsa_put_pub_pem(int output_fd, const t_rsa_pub_key *in)
{
	char			out[1024];
	unsigned char	der_string[1024];
	char			result[1024];
	unsigned		total_size;

	memset(out, 0, sizeof(out));
	memset(der_string, 0, sizeof(der_string));
	memset(result, 0, sizeof(result));
	total_size = rsa_public_to_der_string(in, der_string);
	encode_base64_block_with_padding(der_string, out, total_size);
	strcat(result, PUBLIC_KEY_HEADER);
	strcat(result, out);
	strcat(result, "\n");
	strcat(result, PUBLIC_KEY_BOT);
	total_size = strlen(result);
	if (write(output_fd, result, total_size) == total_size)
		return (0);
	return (1);
}
