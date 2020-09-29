/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsautl_context.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:53:16 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/29 14:53:41 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_RSAUTL_CONTEXT_H
# define FT_SSL_RSAUTL_CONTEXT_H

# include <sys/syslimits.h>

# define RSAUTL_CTX_DECRYPT		0x1U
# define RSAUTL_CTX_HEXDUMP		0x2U
# define RSAUTL_CTX_PUBIN		0x4U

typedef struct		s_rsautl_context
{
	int			inkey_fd;
	int			input_fd;
	int			output_fd;
	unsigned	mode;
}					t_rsautl_context;

t_rsautl_context	*init_rsautl_ctx();
void				delete_rsautl_ctx(t_rsautl_context *ctx);

t_rsautl_context	*parse_rsautl_argv(int argc, char **argv,
									t_rsautl_context *ctx);
t_rsautl_context	*parse_rsa_utl_state_out(int ac, char **av,
									t_rsautl_context *ctx);

#endif
