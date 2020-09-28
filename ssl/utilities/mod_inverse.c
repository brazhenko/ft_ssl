/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_inverse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:51:27 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/28 15:51:27 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// Returns modulo inverse of a with respect
// to m using extended Euclid Algorithm
// Assumption: a and m are coprimes, i.e.,
// gcd(a, m) = 1

__int128 mod_inverse(__int128 a, __int128 m)
{
	__int128 m0 = m;
	__int128 y = 0, x = 1;

	if (m == 1)
		return 0;
	while (a > 1)
	{
		// q is quotient
		__int128 q = a / m;
		__int128 t = m;
		// m is remainder now, process same as
		// Euclid's algo
		m = a % m, a = t;
		t = y;
		// Update y and x
		y = x - q * y;
		x = t;
	}
	// Make x positive
	if (x < 0)
		x += m0;
	return x;
}