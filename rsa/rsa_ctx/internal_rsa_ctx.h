/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_rsa_ctx.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 19:15:41 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/29 19:15:41 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_INTERNAL_RSA_CTX_H
# define FT_SSL_INTERNAL_RSA_CTX_H

# include "rsa_context.h"
# include <stdlib.h>
# include <string.h>

t_rsa_context	*rsa_state_inform(int argc, char **argv, t_rsa_context *ctx);
t_rsa_context	*rsa_state_outform(int argc, char **argv, t_rsa_context *ctx);
void			rsa_unexpected_token_exit(const char *token);

#endif
