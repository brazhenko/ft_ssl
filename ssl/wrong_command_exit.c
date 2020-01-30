/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrong_command_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:22:13 by a17641238         #+#    #+#             */
/*   Updated: 2020/01/30 17:22:13 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void		wrong_command_exit(char *av0, char *command)
{
	nstrprinterror(4,
			av0, ": Error: \'", command, "\' is an invalid command.\n");
	print_ft_ssl_help();
	exit(EXIT_FAILURE);
}
