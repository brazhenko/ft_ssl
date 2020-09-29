/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_genrsa_ctx.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 19:27:18 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/29 19:27:27 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_INTERNAL_GENRSA_CTX_H
# define FT_SSL_INTERNAL_GENRSA_CTX_H

int					set_genrsa_output_file(t_genrsa_context *ctx,
		const char *output_file_name);
void				*gen_rsa_token_needs_arg_exit(char *token);
void				*gen_rsa_unexpected_token_exit(char *token);

#endif
