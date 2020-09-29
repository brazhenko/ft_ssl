/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_rsa.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 19:23:17 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/29 19:26:23 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_INTERNAL_RSA_H
# define FT_SSL_INTERNAL_RSA_H

void	parse_key(t_rsa_context *ctx,
		t_rsa_pub_key *pub_out,
		t_rsa_priv_key *priv_out);
void	print_priv_key(t_rsa_context *ctx, t_rsa_priv_key *k);
void	print_pub_key(t_rsa_context *ctx, const t_rsa_pub_key *k);
void	append_text_int_with_new_line(char *out, __int128 num);
void	process_output(t_rsa_context *ctx,
		t_rsa_pub_key *pub_out,
		t_rsa_priv_key *priv_out);
void	print_text_pub_key(t_rsa_context *ctx, t_rsa_pub_key *k);
void	print_text_priv_key(t_rsa_context *ctx, t_rsa_priv_key *k);
void	print_modulus(t_rsa_context *ctx, __int128 modulus);

#endif
