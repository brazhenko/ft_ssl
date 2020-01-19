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
** 24 vector_ini/no vector_ini
*/

# define MAX_KEY_BYTE_LEN		64
# define CIPHER_SALT_BYTE_LEN	8
# define MAX_IV_DIG_LEN			32
# define DEFAULT_CIPHER_BUFLEN	64
# define CPHR_ISENCRYPTMODE(c) 	(!(c->mode & 0b1U))
# define CPHR_ISDECRYPTMODE(c) 	((c->mode & 	0b1U))
# define CPHR_ISAFLAG(c)		((c)->mode & (1U << 3U))
# define CPHR_ISKEYSET(c)		((c)->mode & (1U << 4U))
# define CPHR_ISPASSSET(c)		((c)->mode & (1U << 5U))
# define CPHR_ISSALTSET(c)		((c)->mode & (1U << 6U))
# define CPHR_ISIVSET(c) 		((c)->mode & (1U << 7U))

# define CIPHER_PASSWORD_PROMPT "enter encryption password:"
# define CIPHER_PASSWORD_VERIFY_PROMPT "Verifying - enter encryption password:"

struct		s_cipher_context
{
	char 		input_file[PATH_MAX];
	char 		output_file[PATH_MAX];
	int 		input_fd;
	int			output_fd;
	size_t		bufsize;
	uint8_t 	key[MAX_KEY_BYTE_LEN];
	char		password[PASS_MAX];
	char		salt[CIPHER_SALT_BYTE_LEN];
	char		vector_ini[MAX_IV_DIG_LEN];
	unsigned  	mode;
	void		*alg_ptr;
};

typedef struct s_cipher_context t_cipher_context;

t_cipher_context	*init_cipher_context(void *cipher_alg_ptr);
void				destruct_cipher_context(t_cipher_context *ctx);

t_cipher_context	*ci_state_a(int argc, char **argv, t_cipher_context *ctx);
t_cipher_context	*ci_state_d(int argc, char **argv, t_cipher_context *ctx);
t_cipher_context	*ci_state_e(int argc, char **argv, t_cipher_context *ctx);
t_cipher_context	*ci_state_i(int argc, char **argv, t_cipher_context *ctx);
t_cipher_context	*ci_state_k(int argc, char **argv, t_cipher_context *ctx);
t_cipher_context	*ci_state_o(int argc, char **argv, t_cipher_context *ctx);
t_cipher_context	*ci_state_p(int argc, char **argv, t_cipher_context *ctx);
t_cipher_context	*ci_state_s(int argc, char **argv, t_cipher_context *ctx);
t_cipher_context	*ci_state_v(int argc, char **argv, t_cipher_context *ctx);

t_cipher_context	*parse_des_argv(t_cipher_context *ctx, int argc, char **argv);

int 	set_cipher_input_file(t_cipher_context *ctx,
		const char *input_file_name);
int		set_cipher_output_file(t_cipher_context *ctx,
		const char *output_file_name);
int		set_cipher_bufsize(t_cipher_context *ctx, const char *argv);
void 	set_cipher_key(t_cipher_context *ctx, char *arg);
void	set_cipher_pass_salt(t_cipher_context *ctx, char *arg);
int 	set_cipher_init_vector(t_cipher_context *ctx, char *arg);
int 	set_cipher_password_from_stdin(t_cipher_context *ctx);
int 	set_cipher_random_pass_salt(t_cipher_context *ctx, size_t bytelen);

#endif
