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

int			command_executor(int ac, char *av[])
{
	if (strcmp(av[0], "md5") == 0)
		hash_executor(ac - 1, av + 1, &md5);
	else if (strcmp(av[0], "sha256") == 0)
		hash_executor(ac - 1, av + 1, &sha256);
	else if (strcmp(av[0], "base64") == 0)
	{
		// encode_executor(ac - 1, av + 1, &base64);
		printf("debug\n");
	}
	else
	{
		nstrprint(16,
				"ft_ssl: Error: \'", av[0], "\' is an invalid command.\n",
				"Standard commands:\n",
				"\n"
				"Message Digest commands:\n",
				"md5\n", "sha256\n",
				"sha384 - under development\n",
				"sha512 - under development\n",
				"Whirlpool - under development\n",
				"\n",
				"Cipher commands:\n",
				"base64 - under development\n",
				"des - under development\n",
				"des-ecb - under development\n",
				"des-cbc - under development\n"
				"\n");
	}
	return (0);
}
