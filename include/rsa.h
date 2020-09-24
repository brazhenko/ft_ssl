//
// Created by 17641238 on 11.07.2020.
//

#ifndef FT_SSL_RSA_H
#define FT_SSL_RSA_H

# define PRIVATE_KEY_HEADER	"-----BEGIN RSA PRIVATE KEY-----"
# define PRIVATE_KEY_BOT	"-----END RSA PRIVATE KEY-----"
# define DEFAULT_PUBLIC_EXP	65537

/*
**  struct s_rsa_priv_key;
** 	__int128	n = p** q
** 	__int128	e - public exponent
**	__int128	d - secret exponent, calculated : d*e % phi = 1
**	__int128	p, q; - 2 master prime numbers
**	__int128	dp - extra component, d % (p-1)
**	__int128	dq - extra component, d % (q-1)
**	__int128	qinv - calculated : q*qinv % p = 1
**
**  Help material:
**  https://crypto.stackexchange.com/questions/
**  21102/what-is-the-ssl-private-key-file-format
*/

typedef struct	s_rsa_priv_key
{
	int			version;
	__int128	n;
	__int128	e;
	__int128	d;
	__int128	p;
	__int128	q;
	__int128	dp;
	__int128	dq;
	__int128	qinv;
}				t_rsa_priv_key;

void	genrsa(int ac, char **av);
void	generate_2_primes_for_key(t_rsa_priv_key *k);

int 	rsa_private_pem_out(const t_rsa_priv_key *in, unsigned char *out);

#endif //FT_SSL_RSA_H
