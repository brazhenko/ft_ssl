/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:36:14 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/29 20:36:15 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

int			main(int ac, char **av, char **en)
{
	(void)en;
	if (ac == 1)
	{
		nstrprinterror(3, "usage: ", av[0], " command [command opts] [command args]\n");
		// write(2, "usage: ft_ssl command [command opts] [command args]\n", 52);
	}
	else
	{
		command_executor(ac, av);
	}
	return (0);
}
