#include "ft_ssl.h"

void		illegal_option_exit(char c)
{
	write(2, "illegal option -- ", 18);
	write(2, &c, 1);
	write(2, "\n", 1);
	exit(1);
}

int			handle_hash_flags(char *str, int *flags)
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
			*flags = *flags | FLAG_S;
		else if (*str == 'p')
		{
			*flags = *flags | FLAG_P;
			md5(NULL, *flags);
			*flags = *flags - FLAG_P;
		}
		else
			illegal_option_exit(*str);
		++str;
	}
	return (0);
}

int			hash_executor(int ac, char *av[], void *(*algo)(char *, int))
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
				handle_hash_flags(av[i], &flags);
			else
			{
				algo(av[i], flags);
				flags &= RESET_FLAG;
			}
			++i;
		}
	}
	else
		algo(NULL, FLAG_P);
	return (0);
}

int			command_executor(int ac, char *av[])
{
	char	*ptr;

	if (strcmp(av[0], "md5") == 0)
		hash_executor(ac - 1, av + 1, md5);
	else if (strcmp(av[0], "sha256") == 0)
	{
		write(2, "sha256 is not available now\n", 28);
		exit(EXIT_FAILURE);
	}
	else
	{
		nstrprint(3, "ft_ssl: Error: \'", av[0], "\' is an invalid command.\n");
		// TODO add the list of available commands
	}
	return (0);
}

// TODO -s after that ONLY files nothing more
// TODO from pipe (or stdin) with -p forward the input to the output
// TODO handle when zero arguments (stdin reading must be started)
