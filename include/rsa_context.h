/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_context.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:52:21 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/29 14:52:24 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_RSA_CONTEXT_H
# define FT_SSL_RSA_CONTEXT_H

# include <sys/syslimits.h>

/*
**	Man pages may help you.
** 	https://www.openssl.org/docs/man1.0.2/man1/openssl-rsa.html
** 	-passin pass https://www.openssl.org/docs/man1.0.2/man1/openssl.html
*/

# define RSA_CTX_MODE_MODULUS	0x1U
# define RSA_CTX_MODE_PUBIN		0x2U
# define RSA_CTX_MODE_PUBOUT	0x4U
# define RSA_CTX_MODE_NOOUT		0x8U
# define RSA_CTX_MODE_TEXT		0x20U

typedef struct	s_rsa_context
{
	int			input_fd;
	int			output_fd;
	unsigned	mode;
	char		inform[64];
	char		outform[64];
}				t_rsa_context;

t_rsa_context	*init_rsa_ctx();
void			delete_rsa_ctx(t_rsa_context *ctx);

t_rsa_context	*rsa_state_in(int argc, char **argv, t_rsa_context *ctx);
t_rsa_context	*rsa_state_out(int argc, char **argv, t_rsa_context *ctx);
t_rsa_context	*parse_rsa_argv(int argc, char **argv, t_rsa_context *ctx);

#endif
