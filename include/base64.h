#ifndef BASE64_H
# define BASE64_H

# include <sys/syslimits.h>
# include "encode_context.h"

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

void 		base64_encode(t_encode_context *ctx);
void 		base64_decode(t_encode_context *ctx);
void		*base64(t_encode_context *ctx);

#endif
