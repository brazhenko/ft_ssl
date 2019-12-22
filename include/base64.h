#ifndef BASE64_H
# define BASE64_H

# include <sys/syslimits.h>

static const char base64_arr[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/'
};

/*
** base64 context part
** ctx.mode {0, 1, ..., 31} Int32.
** BitN    true/false
** 31 decode/encode
** 30 outfile/no outfile
** 29 infile/no infile
*/

struct		s_base64_context
{
	char 		input_file[PATH_MAX];
	char 		output_file[PATH_MAX];
	int 		input_fd;
	int			output_fd;
	unsigned  	mode;
};

# define ISENCODEMODE(c) 	(!(get_base64_mode(c) & 0b1))
# define ISDECODEMODE(c) 	((get_base64_mode(c) & 	0b1))
# define ISOUTFILE(c) 		((get_base64_mode(c) & 	0b10))
# define ISINPFILE(c) 		((get_base64_mode(c) & 	0b100))

typedef struct s_base64_context t_base64_context;

t_base64_context 	*init_base64_context(void);
int 				set_base64_decode_mode(t_base64_context *ctx);
int 				set_base64_encode_mode(t_base64_context *ctx);
int					set_base64_input_file(t_base64_context *ctx,
									const char *input_file_name);
int 				set_base64_output_file(t_base64_context *ctx,
									const char *output_file_name);
int 				get_base64_mode(t_base64_context *ctx);
t_base64_context	*parse_base64_argv(int argc, char **argv);
t_base64_context	*base64_state_d(int argc, char **argv, t_base64_context *ctx);
t_base64_context	*base64_state_e(int argc, char **argv, t_base64_context *ctx);
t_base64_context	*base64_state_i(int argc, char **argv, t_base64_context *ctx);
t_base64_context	*base64_state_o(int argc, char **argv, t_base64_context *ctx);

/*
** base64 FSM part (argv parser)
*/

//


/*
** base64 algorithm part
*/

# define BASE64_READ_LEN	(64)
# define BASE64_OUTPUT_LEN	((((BASE64_READ_LEN + BASE64_READ_LEN%3))/3)*4)

void		*base64(t_base64_context *ctx);

#endif
