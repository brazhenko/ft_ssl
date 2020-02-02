/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_memory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:18:03 by a17641238         #+#    #+#             */
/*   Updated: 2020/01/30 22:18:03 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <utilities.h>
#include <unistd.h>

#define HEX_DIGITS_PER_BYTE 2

static const char	g_hex_digits[] =
{
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

void	print_hex_memory(void *mem, size_t size)
{
	char		*print_buffer;
	size_t		i;

	print_buffer = xmalloc(size * HEX_DIGITS_PER_BYTE);
	i = 0;
	while (i < size)
	{
		print_buffer[i * HEX_DIGITS_PER_BYTE] =
		g_hex_digits[(((unsigned char *)mem)[i]) >> 4U];
		print_buffer[i * HEX_DIGITS_PER_BYTE + 1] =
		g_hex_digits[(((unsigned char *)mem)[i]) & 0b1111U];
		i++;
	}
	write(STDOUT_FILENO, print_buffer, size * HEX_DIGITS_PER_BYTE);
	write(STDOUT_FILENO, "\n", 1);
}
