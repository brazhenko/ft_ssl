/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_io.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:46:14 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/29 14:49:16 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_KEY_IO_H
# define FT_SSL_KEY_IO_H

# include "rsa.h"
# include "rsa_context.h"

/*
** Functions below produce i/o work.
** Return value:
** 0 - OK
** 1 - Error
*/

/*
** Input
*/

/*
** Private Key
*/

int		rsa_parse_priv_der(int input_fd, t_rsa_priv_key *out);
int		rsa_parse_priv_pem(int input_fd, t_rsa_priv_key *out);

/*
** Public Key
*/

int		rsa_parse_pub_der(int input_fd, t_rsa_pub_key *out);
int		rsa_parse_pub_pem(int input_fd, t_rsa_pub_key *out);

/*
** Output
*/

/*
** Private Key
*/

int		rsa_put_priv_der(int output_fd, const t_rsa_priv_key *in);
int		rsa_put_priv_pem(int output_fd, const t_rsa_priv_key *in);

/*
** Public Key
*/

int		rsa_put_pub_der(int output_fd, const t_rsa_pub_key *in);
int		rsa_put_pub_pem(int output_fd, const t_rsa_pub_key *in);

#endif
