/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 23:02:40 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/29 23:02:42 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

/*
**		arr[0] - iterator for av, arr[1] - hash flags
*/

void		parse_string_param(int ac, char **av, int arr[2],
									void *(*hash_algo)(char *, int))
{
	if (arr[1] & FLAG_S)
	{
		if (++(arr[0]) < ac)
		{
			hash_algo(av[arr[0]], arr[1]);
			arr[1] = arr[1] | ARGS_APPEARED;
			arr[1] = arr[1] - FLAG_S;
		}
		else
			s_param_error_exit();
	}
}

void		hash_executor(int ac, char *av[], void *(*hash_algo)(char *, int))
{
	int		arr[2];

	arr[0] = 0;
	arr[1] = 0;
	while (arr[0] < ac)
	{
		if (is_flag(av[arr[0]]) && !(arr[1] & FARGS_APPEARED))
		{
			parse_hash_flags(av[arr[0]], &arr[1], hash_algo);
			parse_string_param(ac, av, arr, hash_algo);
		}
		else
		{
			hash_algo(av[arr[0]], arr[1]);
			arr[1] = arr[1] | ARGS_APPEARED;
			arr[1] = arr[1] | FARGS_APPEARED;
			arr[1] &= RESET_FLAG;
		}
		arr[0]++;
	}
	if (!(arr[1] & ARGS_APPEARED))
		hash_algo(NULL, arr[1] + FLAG_STDIN);
}
