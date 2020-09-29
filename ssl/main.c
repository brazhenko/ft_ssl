/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:36:14 by lreznak-          #+#    #+#             */
/*   Updated: 2020/09/29 19:44:07 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

int			main(int ac, char **av)
{
	if (ac == 1)
	{
		nstrprinterror(3, "usage: ", av[0],
			" command [command opts] [command args]\n");
	}
	else
	{
		command_executor(ac, av);
	}
	return (0);
}
