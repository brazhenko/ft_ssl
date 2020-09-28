/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genrsa_context.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:46:07 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/28 16:46:07 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_GENRSA_CONTEXT_H
#define FT_SSL_GENRSA_CONTEXT_H

#include <sys/syslimits.h>

typedef struct	s_genrsa_context
{
	char		output_file[PATH_MAX];
	int			output_fd;
}				t_genrsa_context;

t_genrsa_context	*init_gen_rsa_ctx();
void 				delete_gen_rsa_ctx(t_genrsa_context *ctx);

t_genrsa_context	*genrsa_state_i(int argc, char **argv, t_genrsa_context *c);
t_genrsa_context	*genrsa_state_o(int argc, char **argv, t_genrsa_context *c);
t_genrsa_context	*parse_gen_rsa_argv(int argc, char **argv);

#endif //FT_SSL_GENRSA_CONTEXT_H
