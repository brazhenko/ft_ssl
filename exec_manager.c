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
			handle_arg(str, flags);
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
			// TODO stdin hashing
		}
		else
			illegal_option_exit(*str);
		++str;
	}
	return (0);
}

int			handle_arg(char *str, int *flags)
{
	if (*flags & FLAG_Q)
	{
		if (*flags & FLAG_S)
			md5(str, flags);
		else
			md5(str, flags);
		fflush(stdout);
		write(1, "\n", 1);
	}
	else
	{
		if (*flags & FLAG_R)
		{
			md5(str, flags);
			fflush(stdout);
			write(1, " \"", 2);
			write(1, str, strlen(str));
			write(1, "\"", 1);
			write(1, "\n", 1);
		}
		else
		{
			write(1, "MD5 (\"", 6);
			write(1, str, strlen(str));
			write(1, "\"", 1);
			write(1, ") = ", 4);
			md5(str, flags);
			fflush(stdout);
			write(1, "\n", 1);
		}
	}
		return (0);
}

int			hash_executor(int ac, char *av[], void *(*algo)(const char *, int *))
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
				handle_arg(av[i], &flags);
			++i;
		}
	}
	else
	{
		read(1, NULL, 1);
	}
	return (0);
}

int			command_executor(int ac, char *av[])
{
	if (strcmp(av[0], "md5") == 0)
	{
		hash_executor(ac - 1, av + 1, md5);
	}
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