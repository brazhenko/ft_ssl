/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:03:13 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/28 23:03:15 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "sha256.h"
# include "utilities.h"

# define FLAG_R 		0b0000000000000001
# define FLAG_Q 		0b0000000000000010
# define FLAG_S 		0b0000000000000100
# define FLAG_P 		0b0000000000001000
# define FLAG_STDIN 	0b0000000000010000
# define ARGS_APPEARED  0b0000000000100000
# define FARGS_APPEARED	0b0000000001000000
# define RESET_FLAG     0b1111111101110011

typedef uint32_t		t_reg32;

void		*md5(char *str, int flags);
int			command_executor(int ac, char *av[]);

#endif
