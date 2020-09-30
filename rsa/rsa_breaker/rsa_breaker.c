/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_breaker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:22:44 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/29 20:35:44 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rsa.h>
#include "utilities.h"
#include "key_io.h"
#include <fcntl.h>
#include <string.h>

void		find_divisors(uint64_t modulus)
{
	uint64_t		t;
	const uint64_t	board = modulus / 2;
	char			out[64];

	t = 2;
	nstrprint(1, "\aCracking...\n");
	while (t < board)
	{
		if (modulus % t == 0)
		{
			memset(out, 0, sizeof(out));
			int128toa((__int128)t, out);
			nstrprint(3, "Divisor: ", out, "\n");
		}
		t++;
	}
	nstrprint(1, "\aDone...\n");
}

void		rsa_breaker(int ac, char **av)
{
	t_rsa_pub_key	pub_key;
	int				fd;

	if (ac != 1)
		fatal("rsa_breakers needs one arg - 64 pub key to break");
	fd = open(*av, O_RDONLY);
	if (fd < 0)
		fatal("Error with opening key file");
	if (rsa_parse_pub_pem(fd, &pub_key) == 1)
		fatal("Error with input key");
	find_divisors(pub_key.n);
}
