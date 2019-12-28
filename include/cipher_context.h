#ifndef CIPHER_CONTEXT_H
#define CIPHER_CONTEXT_H

#include <limits.h>
#include <stdlib.h>
/*
** Cipher context part
** s_cipher_context.mode = {0, 1, ..., 30, 31} UInt32.
** BitN    true/false
** 31 decode/encode
** 30 outfile/no outfile
** 29 infile/no infile
** 28 -a/ not -a ???
** 27 key/no key
** 26 pass/no pass
** 25 salt/no salt
** 24 vector/no vector
*/

# define DEFAULT_CIPHER_BUFLEN	64
# define ISENCODEMODE(c) 	(!(c->mode & 0b1))
# define ISDECODEMODE(c) 	((c->mode & 	0b1))

struct		s_cipher_context
{
	char 		input_file[PATH_MAX];
	char 		output_file[PATH_MAX];
	int 		input_fd;
	int			output_fd;
	size_t		bufsize;
	char		key[123]; 			// TODO fix hardcode
	char		password[PASS_MAX]; // here too
	char		salt[1024];			// and here
	char		vector[10];			// here
	unsigned  	mode;
};

typedef struct s_cipher_context t_cipher_context;

t_cipher_context	*init_des_context(void);

t_cipher_context	*ci_state_a(int argc, char **argv, t_cipher_context *ctx);
t_cipher_context	*ci_state_d(int argc, char **argv, t_cipher_context *ctx);
t_cipher_context	*ci_state_e(int argc, char **argv, t_cipher_context *ctx);
t_cipher_context	*ci_state_i(int argc, char **argv, t_cipher_context *ctx);
t_cipher_context	*ci_state_k(int argc, char **argv, t_cipher_context *ctx);
t_cipher_context	*ci_state_o(int argc, char **argv, t_cipher_context *ctx);
t_cipher_context	*ci_state_p(int argc, char **argv, t_cipher_context *ctx);
t_cipher_context	*ci_state_s(int argc, char **argv, t_cipher_context *ctx);
t_cipher_context	*ci_state_v(int argc, char **argv, t_cipher_context *ctx);

t_cipher_context	*parse_des_argv(int argc, char **argv);

int 	set_cipher_input_file(t_cipher_context *ctx,
		const char *input_file_name);
int		set_cipher_output_file(t_cipher_context *ctx,
		const char *output_file_name);
int		set_cipher_bufsize(t_cipher_context *ctx, const char *argv);
#endif
