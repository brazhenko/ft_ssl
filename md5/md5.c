/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:42:06 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/29 20:42:07 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

int			init_md5_hash(t_hash_md5 *hash)
{
	hash->a = 0x67452301;
	hash->b = 0xEFCDAB89;
	hash->c = 0x98BADCFE;
	hash->d = 0x10325476;
	return (0);
}

void		*md5(char *str, int flags)
{
	t_hash_md5		hash;

	init_md5_hash(&hash);
	if (flags & FLAG_P || flags & FLAG_STDIN)
		hash = calculate_md5_from_stdin(flags & FLAG_P);
	else if (flags & FLAG_S)
		hash = calculate_md5_from_string(str);
	else
		hash = calculate_md5_from_file(str);
	print_md5(hash, str, flags);
	return (NULL);
}
