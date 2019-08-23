#include "ft_ssl.h"

int			is_flag(const char *str)
{
	if (str && str[0] == '-' && str[1] != '\0')
		return (1);
	return (0);
}

void		illegal_option_exit(char c)
{
	write(2, "illegal option -- ", 18);
	write(2, &c, 1);
	write(2, "\n", 1);
	exit(1);
}

int			handle_flag(char *str, int *flags)
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
				handle_flag(av[i], &flags);
			else
			{
				algo(av[i], flags);
				flags &= RESET_FLAG_PS;
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
	if (strcmp(av[0], "md5") == 0)
		hash_executor(ac - 1, av + 1, md5);
	else if (strcmp(av[0], "sha256") == 0)
	{
		write(2, "sha256 is not available now\n", 28);
	}
	else
	{
		write(2, "ft_ssl: Error: \'", 16);
		write(2, av[0], strlen(av[0]));
		write(2, "\' is an invalid command.\n", 25);
	}
	return (0);
}