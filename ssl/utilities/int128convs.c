/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int128convs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:46:25 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/30 13:38:28 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

void	int128toa(t_uint128 in, char *out)
{
	char *out_copy;
	char c;

	*out = '0';
	out_copy = out;
	while (in)
	{
		*out = (char)((in % 10) + '0');
		out++;
		in /= 10;
	}
	out--;
	while (out_copy < out)
	{
		c = *out_copy;
		*out_copy = *out;
		*out = c;
		out_copy++;
		out--;
	}
}

void	int128tohex(t_uint128 in, char *out, const char *alphabet)
{
	char *out_copy;
	char c;
	char tmp;

	*out = '0';
	out_copy = out;
	while (in)
	{
		tmp = (char)(in % 16);
		*out = alphabet[(int)tmp];
		out++;
		in /= 16;
	}
	out--;
	while (out_copy < out)
	{
		c = *out_copy;
		*out_copy = *out;
		*out = c;
		out_copy++;
		out--;
	}
}
