#include <cxxabi.h>
#include "rsa.h"
#include "base64.h"
#include <string.h>
#include <stdio.h>

static void	genrate_to_primes_for_key(t_rsa_priv_key *k)
{

}


/*
**	 generates 64 private key
*/

void	genrsa(int ac, char **av)
{
	uint64_t d = 7663513159760580577U;
	uint64_t n = 11291703101467197271U;
	t_rsa_priv_key	k;

	memset(&k, 0, sizeof(k));

	char arr[128];
	memset(arr, 0, 128);

	encode_base64_block((unsigned char*)&d, arr, sizeof(d));
	printf("%s\n", arr);

	encode_base64_block((unsigned char*)&n, arr, sizeof(d));
	printf("%s\n", arr);
}

//https://crypto.stackexchange.com/questions/21102/what-is-the-ssl-private-key-file-format

// 30
// 3e // bytecount!

// 02 01b Type[00] // RSA 2 primes
// 02 09b N[00c91e44827012371d]
// 02 03b E[010001]
// 02 08b D[6745377fa9c621b1]
// 02 05b P[00eb4c25fb]
// 02 05b Q[00dad043c7]
// 02 05b D mod (P-1) [00af938fd7]
// 02 04b D mod (Q-1) [0544c27d]
// 02 04b §[46b87a0e]