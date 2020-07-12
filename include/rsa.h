//
// Created by 17641238 on 11.07.2020.
//

#ifndef FT_SSL_RSA_H
#define FT_SSL_RSA_H

# define PRIVATE_KEY_HEADER	"-----BEGIN RSA PRIVATE KEY-----\n"
# define PRIVATE_KEY_BOT	"-----END RSA PRIVATE KEY-----\n"
# define DEFAULT_PUBLIC_EXP	65537

typedef struct	s_rsa_priv_key
{
	int			version;
	__int128	modulus_n;
	__int128	public_exponent_e;
	__int128	privateExponent_d;
	__int128	p;
	__int128	q;
	__int128	exp1;
	__int128	exp2;
	__int128	coefficient;
}				t_rsa_priv_key;

void	genrsa(int ac, char **av);

#endif //FT_SSL_RSA_H
