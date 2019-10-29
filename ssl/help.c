/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:27:28 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/29 22:27:29 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "utilities.h"

void		print_usage(void)
{
	nstrprinterror(1, "usage: md5 [-pqrtx] [-s string] [files ...]\n");
}

void		illegal_hash_option_exit(char c)
{
	write(2, "illegal option -- ", 18);
	write(2, &c, 1);
	write(2, "\n", 1);
	print_usage();
	exit(EXIT_FAILURE);
}

void		s_param_error_exit(void)
{
	nstrprinterror(1, "ft_ssl: option requires an argument -- s\n");
	print_usage();
	exit(EXIT_FAILURE);
}
