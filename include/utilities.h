/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:03:21 by lreznak-          #+#    #+#             */
/*   Updated: 2020/09/27 21:52:22 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include <stdint.h>
# include <stddef.h>
#include <stdbool.h>

static const char		g_hex_arr[] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'a', 'b',
	'c', 'd', 'e', 'f'
};

char		*nstrjoin(int n, ...);
int			nstrprint(int n, ...);
int			nstrprinterror(int n, ...);
int			is_flag(const char *str);
void		*xmalloc(size_t size);
void		print_uint32_bits(unsigned num);
void		print_uint64_bits(uint64_t num);
void		*mem_xor(void *left, void *right, void *out, size_t len);
void		print_hex_memory(void *mem, size_t size);
size_t		max1(size_t l, size_t r);
size_t		min1(size_t l, size_t r);
int			miller_rabin_test(uint64_t n, int k);
bool		is_prime(uint64_t num);
uint64_t 	mod_pow(uint64_t n, uint64_t pw, uint64_t mod);
uint64_t 	fast_mod_pow(unsigned __int128 base, unsigned __int128  pw, unsigned __int128 mod);
void		bezout(__int128 a, __int128 b, __int128 *xout, __int128 *yout);
void 		fatal(const char *s);

#endif
