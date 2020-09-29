/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rsautl_internal.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 19:01:55 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/29 19:03:02 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_PARSE_RSAUTL_INTERNAL_H
# define FT_SSL_PARSE_RSAUTL_INTERNAL_H

t_rsautl_context	*parse_rsa_utl_state_inkey(int ac, char **argv,
											t_rsautl_context *ctx);
void				rsautl_unexpected_token_exit(const char *token);

#endif
