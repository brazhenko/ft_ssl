/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:03:21 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/28 23:03:23 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

#include <stdint.h>
# include <stddef.h>
# define MAX(x, y) ((x) > (y) ? (x) : (y))

static const char		g_hex_arr[] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'a', 'b',
	'c', 'd', 'e', 'f'
};

char	*nstrjoin(int n, ...);
int		nstrprint(int n, ...);
int		nstrprinterror(int n, ...);
int		is_flag(const char *str);
void	*xmalloc(size_t size);
void	print_uint32_bits(unsigned num);
void	print_uint64_bits(uint64_t num);
void 	*mem_xor(void *left, void *right, void *out, size_t len);
void	print_hex_memory(void *mem, size_t size);
#endif
