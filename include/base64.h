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

static const char base64_dec_arr[] = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, // 000
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, // 020
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, // 040
	0x0, 0x0, 0x0,  62, 0x0, 0x0, 0x0,  63,
	 52,  53,  54,  55,  56,  57,  58,  59, // 060
	 60,  61, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, // 070
	0x0,   0,   1,   2,   3,   4,   5,   6, // 100
	  7,   8,   9,  10,  11,  12,  13,  14,
	 15,  16,  17,  18,  19,  20,  21,  22, // 120
	 23,  24,  25, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0,  26,  27,  28,  29,  30,  31,  32, // 140
	 33,  34,  35,  36,  37,  38,  39,  40,
	 41,  42,  43,  44,  45,  46,  47,  48, // 160
	 49,  50,  51, 0x0, 0x0, 0x0, 0x0, 0x0,
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

# define ISENCODEMODE(c) 	(!(c->mode & 0b1))
# define ISDECODEMODE(c) 	((c->mode & 	0b1))
# define ISOUTFILE(c) 		((c->mode & 	0b10))
# define ISINPFILE(c) 		((c->mode & 	0b100))

typedef struct s_base64_context t_base64_context;

t_base64_context 	*init_base64_context(void);
int 				set_base64_decode_mode(t_base64_context *ctx);
int 				set_base64_encode_mode(t_base64_context *ctx);
int					set_base64_input_file(t_base64_context *ctx, const char *input_file_name);
int 				set_base64_output_file(t_base64_context *ctx, const char *output_file_name);
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

/*
** N.B.
** BASE64_ENCODE_READ_LEN macro must be so that
** (BASE64_ENCODE_READ_LEN % 3 == 0)
** cuz calculation buffer depends on it
*/

# define BASE64_ENCODE_READ_LEN		(63)
# define BASE64_ENCODE_OUTPUT_LEN	(((((BASE64_ENCODE_READ_LEN))/3)*4)+1)

/*
** N.B.
** BASE64_DECODE_READ_LEN macro must be so that
** (BASE64_DECODE_READ_LEN % 4 == 0)
** cuz calculation buffer depends on it
*/

# define BASE64_DECODE_READ_LEN		(84)
# define BASE64_DECODE_OUTPUT_LEN	((BASE64_DECODE_READ_LEN)/4*3)

void 		base64_decode(t_base64_context *ctx);
void		*base64(t_base64_context *ctx);

#endif
