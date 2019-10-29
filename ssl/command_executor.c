/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:39:11 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/29 20:39:12 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void		illegal_hash_option_exit(char c)
{
	write(2, "illegal option -- ", 18);
	write(2, &c, 1);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

int			parse_hash_flags(char *str, int *flags, void *(*hash_algo)(char *, int))
{
	++str;
	while (*str)
	{
		if (*flags & FLAG_S)
		{
			hash_algo(str, *flags);
			*flags -= FLAG_S;
			return (0);
		}
		else if (*str == 'r')
			*flags = *flags | FLAG_R;
		else if (*str == 'q')
			*flags = *flags | FLAG_Q;
		else if (*str == 's')
		{
			if (*(str + 1))
			{
				hash_algo(str + 1, *flags + FLAG_S);
				*flags = *flags + ARGS_APPEARED;
				return (0);
			}
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

int			hash_executor(int ac, char *av[], void *(*hash_algo)(char *, int))
{
	int		i;
	int		flags;

	i = 0;
	flags = 0;
	while (i < ac)
	{
		if (is_flag(av[i]) && !(flags & FARGS_APPEARED))
		{
			parse_hash_flags(av[i], &flags, hash_algo);
			if (flags & FLAG_S)
			{
				if (++i < ac)
				{
					hash_algo(av[i], flags);
					flags = flags | ARGS_APPEARED;
					flags = flags - FLAG_S;
				}
				else
				{
					write(1, "-s error\n", 9);
					// TODO print usage
					exit(EXIT_FAILURE);
				}
			}
		}
		else
		{
			hash_algo(av[i], flags);
			flags = flags | ARGS_APPEARED;
			flags = flags | FARGS_APPEARED;
			flags &= RESET_FLAG;
		}
		++i;
	}
	if (!(flags & ARGS_APPEARED))
	{
		hash_algo(NULL, flags + FLAG_STDIN);
	}
	return (0);
}

int			command_executor(int ac, char *av[])
{
	if (strcmp(av[0], "md5") == 0)
		hash_executor(ac - 1, av + 1, &md5);
	else if (strcmp(av[0], "sha256") == 0)
		hash_executor(ac - 1, av + 1, &sha256);
	else
	{
		nstrprint(13,
				"ft_ssl: Error: \'", av[0], "\' is an invalid command.\n",
				"Standard commands:\n",
				"\n"
				"Message Digest commands:\n",
				"md5\n", "sha256\n",
				"sha384 - under development\n",
				"sha512 - under development\n",
				"Whirlpool - under development\n",
				"\n",
				"Cipher commands:\n", "\n");
	}
	return (0);
}
