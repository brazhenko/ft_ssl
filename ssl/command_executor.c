/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:39:11 by lreznak-          #+#    #+#             */
/*   Updated: 2020/09/28 17:17:58 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "des.h"
#include "rsa.h"

int			command_executor(int ac, char *av[])
{
	if (strcmp(av[1], "md5") == 0)
		hash_executor(ac - 2, av + 2, &md5);
	else if (strcmp(av[1], "sha256") == 0)
		hash_executor(ac - 2, av + 2, &sha256);
	else if (strcmp(av[1], "base64") == 0)
		encode_executor(ac - 2, av + 2, &base64);
	else if (strcmp(av[1], "des") == 0 || strcmp(av[1], "des-cbc") == 0)
		cipher_executor(ac - 2, av + 2, &des_cbc);
	else if (strcmp(av[1], "des-ecb") == 0)
		cipher_executor(ac - 2, av + 2, &des_ecb);
	else if (strcmp(av[1], "genrsa") == 0)
		genrsa(ac - 2, av + 2);
	else if (strcmp(av[1], "rsautl") == 0)
		rsautl(ac - 2, av + 2);
	else if (strcmp(av[1], "rsa") == 0)
		rsa(ac - 2, av + 2);
	else if (strcmp(av[1], "rsa_breaker") == 0)
		rsa_breaker(ac - 2, av + 2);
	else
		wrong_command_exit(av[0], av[1]);
	return (EXIT_SUCCESS);
}
