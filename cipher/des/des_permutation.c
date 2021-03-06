/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_permutation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:34:35 by a17641238         #+#    #+#             */
/*   Updated: 2020/01/30 17:34:35 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <utilities.h>

/*
** des_permutation() takes
** input[] of any len,
** output[] of arr_len / CHAR_BIT
** permutation arr[] of arr_len
** arr_len
**
** The following function enumerates BITS of input[] and output[],
** puts to Ns bit of output[] arr[N]s bit for input[].
** N.B. input pointer can equals output pointer.
**
** if parameters are wrong behaviour is undefined
*/

void			des_permutation(unsigned char *input,
							unsigned char *output,
							const size_t *arr,
							size_t arr_len)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = xmalloc(arr_len / CHAR_BIT);
	memset(tmp, 0, arr_len / CHAR_BIT);
	i = 0;
	while (i < arr_len)
	{
		tmp[i / CHAR_BIT] |= (((input[arr[i] / 8u] >>
		(8u - (arr[i] & 7u) - 1u)) & 1u) << (8u - (i & 7u) - 1u));
		i++;
	}
	memcpy(output, tmp, arr_len / CHAR_BIT);
	free(tmp);
}
