/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_context.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:37:42 by a17641238         #+#    #+#             */
/*   Updated: 2020/02/03 11:37:55 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCODE_CONTEXT_H
# define ENCODE_CONTEXT_H

# include <sys/syslimits.h>

/*
** encode context part
** s_encode_context.mode = {0, 1, ..., 31} Int32.
** BitN    true/false
** 31 decode/encode
** 30 outfile/no outfile
** 29 infile/no infile
*/

typedef struct		s_encode_context
{
	char		input_file[PATH_MAX];
	char		output_file[PATH_MAX];
	int			input_fd;
	int			output_fd;
	unsigned	mode;
}					t_encode_context;

# define ISENCODEMODE(c) 	(!(c->mode & 0b1))
# define ISDECODEMODE(c) 	((c->mode & 0b1))

t_encode_context	*init_encode_context(void);
void				destruct_encode_context(t_encode_context *ctx);
int					set_encode_decode_mode(t_encode_context *ctx);
int					set_encode_encode_mode(t_encode_context *ctx);
int					set_encode_input_file(t_encode_context *ctx,
									const char *input_file_name);
int					set_encode_output_file(t_encode_context *ctx,
		const char *output_file_name);

/*
** encode FSM part (argv parser)
*/

t_encode_context	*parse_encode_argv(int ac, char **av);
t_encode_context	*encode_state_d(int ac, char **av, t_encode_context *ctx);
t_encode_context	*encode_state_e(int ac, char **av, t_encode_context *ctx);
t_encode_context	*encode_state_i(int ac, char **av, t_encode_context *ctx);
t_encode_context	*encode_state_o(int ac, char **av, t_encode_context *ctx);

/*
** encode help, encode etc.
*/

void				encode_option_requires_argument_exit(const char *opt);
void				encode_invalid_option_exit(const char *opt);
void				encode_usage(void);
void				encode_print_usage_exit(void);

#endif
