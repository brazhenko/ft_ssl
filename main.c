#include "ft_ssl.h"

int			main(int ac, char *av[], char *en[])
{
	(void)en;

	if (ac == 1)
	{
		write(2, "usage: ft_ssl command [command opts] [command args]\n", 52);
	}
	else
	{
		command_executor(ac - 1, av + 1);
	}
	return (0);
}