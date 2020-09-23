//
// Created by 17641238 on 14.07.2020.
//

#include <utilities.h>
#include "rsa.h"
// 30
// 3e
// 02 01 00
// 02 09 N [00b17b011e5bd7690f]
// 02 03 010001
// 02 08 4cd2101e29b6fda1
// 02 05 P [00e7d73ad1]
// 02 05 Q [00c3f99ddf]
// 02 05 0096eeee21
// 02 04 49ab4009
// 02 04 21fdf0b4

//https://crypto.stackexchange.com/questions/21102/what-is-the-ssl-private-key-file-format

// 30
// 82 01 3b
// 02
// 01 00
// 02 41 00c2e1f01c4c126ff1fb00e3a5c30078200d54551f29da7d5d1d87e1502708aedbdf1e92043d2fabf7b98b2a7eccf0cc886d80dbadf1e9e40245b50e5cca54d6dc445a00a4e3

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

// 30 24 30 0d   0609 [2a864886f70d010101] 05    0003 130030 10 0209 [00d635fd3f98395ab5] 0203 [010001]

int 	rsa_private_pem_out(t_rsa_priv_key *in, const char *outfile)
{
	__int128 x = 0xc91e44827012371d;
	// print_hex_memory(&x, sizeof(x));
	return 0;
}

int 	rsa_private_pem_in(t_rsa_priv_key *out, const char *infile)
{
	return 0;
}