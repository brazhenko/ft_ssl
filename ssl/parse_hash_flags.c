/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 23:02:40 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/29 23:02:42 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static int	parse_string_argument(char *str, int *flags,
		void *(*hash_algo)(char *, int))
{
	hash_algo(str, *flags);
	*flags -= FLAG_S;
	return (0);
}

static int	parse_stringflag_argument(char *str, int *flags,
		void *(*hash_algo)(char *, int))
{
	hash_algo(str + 1, *flags + FLAG_S);
	*flags = *flags + ARGS_APPEARED;
	return (0);
}

int			parse_hash_flags(char *str, int *flags,
		void *(*hash_algo)(char *, int))
{
	++str;
	while (*str)
	{
		if (*flags & FLAG_S)
			return (parse_string_argument(str, flags, hash_algo));
		else if (*str == 'r')
			*flags = *flags | FLAG_R;
		else if (*str == 'q')
			*flags = *flags | FLAG_Q;
		else if (*str == 's')
		{
			if (*(str + 1))
				return (parse_stringflag_argument(str, flags, hash_algo));
			*flags = *flags | FLAG_S;
		}
		else if (*str == 'p')
		{
			hash_algo(NULL, *flags + FLAG_P);
			*flags |= ARGS_APPEARED;
		}
		else
			illegal_hash_option_exit(*str);
		++str;
	}
	return (0);
}
