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
//	else if (strcmp(av[1], "des-cfb") == 0)
//		cipher_executor(ac - 2, av + 2, &des_cfb);
//	else if (strcmp(av[1], "des-ofb") == 0)
//		cipher_executor(ac - 2, av + 2, &des_ofb);
//	else if (strcmp(av[1], "des-ctr") == 0)
//		cipher_executor(ac - 2, av + 2, &des_ctr);
//	else if (strcmp(av[1], "3des") == 0)
//		cipher_executor(ac - 2, av + 2, &des_3des);
	else
		wrong_command_exit(av[0], av[1]);
	return (EXIT_SUCCESS);
}
