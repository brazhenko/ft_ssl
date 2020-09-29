/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:50:43 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/29 19:12:34 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_RSA_H
# define FT_SSL_RSA_H

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
**	21102/what-is-the-ssl-private-key-file-format
**
**  https://stackoverflow.com/questions/
** 	55803033/rsa-public-key-bit-string-format
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

typedef struct	s_rsa_pub_key
{
	__int128	oid;
	__int128	n;
	__int128	e;

}				t_rsa_pub_key;

void			genrsa(int ac, char **av);
void			generate_2_primes_for_key(t_rsa_priv_key *k);

void			rsa(int ac, char **av);
void			rsautl(int ac, char **av);
void 			rsa_breaker(int ac, char **av);

#endif
