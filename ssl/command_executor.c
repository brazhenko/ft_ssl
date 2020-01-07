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
#include "des.h"

int			command_executor(int ac, char *av[])
{
	if (strcmp(av[1], "md5") == 0)
		hash_executor(ac - 2, av + 2, &md5);
	else if (strcmp(av[1], "sha256") == 0)
		hash_executor(ac - 2, av + 2, &sha256);
	else if (strcmp(av[1], "base64") == 0)
		encode_executor(ac - 2, av + 2, &base64);
	else if (strcmp(av[1], "des") == 0)
		cipher_executor(ac - 2, av + 2, &des_cbc);
	else if (strcmp(av[1], "des-ecb") == 0)
		cipher_executor(ac - 2, av + 2, &des_ecb);
	else if (strcmp(av[1], "des-cbc") == 0)
		cipher_executor(ac - 2, av + 2, &des_cbc);
	else if (strcmp(av[1], "des-cfb") == 0)
		cipher_executor(ac - 2, av + 2, &des_cfb);
	else if (strcmp(av[1], "des-ofb") == 0)
		cipher_executor(ac - 2, av + 2, &des_ofb);
	else if (strcmp(av[1], "des-ctr") == 0)
		cipher_executor(ac - 2, av + 2, &des_ctr);
	else if (strcmp(av[1], "3des") == 0)
		cipher_executor(ac - 2, av + 2, &des_3des);
	else
	{
		nstrprinterror(19,
				av[0], ": Error: \'", av[1], "\' is an invalid command.\n",
				"Standard commands:\n",
				"\n"
				"Message Digest commands:\n",
				"md5\n", "sha256\n",
				"sha384 - under development\n",
				"sha512 - under development\n",
				"Whirlpool - under development\n",
				"\n",
				"Encoding commands:\n",
				"base64\n",
				"\n",
				"Cipher commands:\n",
				"des - under development\n",
				"des-ecb - under development\n",
				"des-cbc - under development\n"
				"\n");
	}
	return (0);
}
