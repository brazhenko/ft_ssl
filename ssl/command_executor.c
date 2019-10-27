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
			md5(str, *flags);
			*flags -= FLAG_S;
			return 1;
		}
		if (*str == 'r')
			*flags = *flags | FLAG_R;
		else if (*str == 'q')
			*flags = *flags | FLAG_Q;
		else if (*str == 's')
		{
			*flags = *flags | FLAG_S;
			if (*(str + 1))
			{
				hash_algo(str + 1, *flags);
				*flags = *flags - FLAG_S;
				return (0);
			}
		}
		else if (*str == 'p')
		{
			hash_algo(NULL, *flags);
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
	if (ac)
	{
		while (i < ac)
		{
			if (is_flag(av[i]))
			{
				parse_hash_flags(av[i], &flags, hash_algo);
				if (flags & FLAG_S)
				{
					if (++i < ac)
					{
						hash_algo(av[i], flags);
						flags = flags - FLAG_S;
					}
					else
					{
						write(1, "-s error\n", 9);
						exit(EXIT_FAILURE);
					}
				}
			}
			else
			{
				hash_algo(av[i], flags);
				flags &= RESET_FLAG;
			}
			++i;
		}
	}
	else
		hash_algo(NULL, FLAG_P);
	return (0);
}

int			command_executor(int ac, char *av[])
{
	char	*ptr;

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
				"Cipher commands:\n", "\n"
				);
	}
	return (0);
}

// TODO -s after that ONLY files nothing more
// TODO from pipe (or stdin) with -p forward the input to the output
// TODO parse when zero arguments (stdin reading must be started)
