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

# include "sha256.h"
# include "md5.h"
# include "base64.h"

# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "cipher_context.h"
# include "utilities.h"

# define FLAG_R 		0b0000000000000001
# define FLAG_Q 		0b0000000000000010
# define FLAG_S 		0b0000000000000100
# define FLAG_P 		0b0000000000001000
# define FLAG_STDIN 	0b0000000000010000
# define ARGS_APPEARED  0b0000000000100000
# define FARGS_APPEARED	0b0000000001000000
# define RESET_FLAG     0b1111111101110011

# define BUFLEN			5120

typedef uint32_t			t_reg32;

void		*md5(char *str, int flags);
int			command_executor(int ac, char *av[]);
void		hash_executor(int ac, char *av[], void *(*hash_algo)(char *, int));
void		encode_executor(int ac, char *av[],
		void *(*algo)(t_encode_context *ctx));
int			parse_hash_flags(char *str, int *flags,
					void *(*hash_algo)(char *, int));
void		print_usage(void);
void		illegal_hash_option_exit(char c);
void		s_param_error_exit(void);
void		cipher_executor(int ac, char **av,
					void *(*algo)(t_cipher_context *));
void		print_ft_ssl_help(void);
void		wrong_command_exit(char *av0, char *command);

#endif
