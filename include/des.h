#ifndef DES_H
#define DES_H

# include <stdint.h>
# include "cipher_context.h"
# include <limits.h>
# include <unistd.h>

# define DES_CIPHER_BLOCK_LEN	(64/(CHAR_BIT))
# define DES_CIPHER_BIT_LEN		(64)

typedef		uint8_t		DESBLOCK[8];
typedef		DESBLOCK	*LPDESBLOCK;
typedef		uint8_t 	DESHALFBLOCK[4];
typedef		uint8_t		*LPDESHALFBLOCK;

ssize_t		des_get_block(t_cipher_context *ctx, LPDESBLOCK block);

void		*des_ecb(t_cipher_context *ctx);
void 		des_ecb_encode(t_cipher_context *ctx);
void 		des_ecb_decode(t_cipher_context *ctx);

void		*des_cbc(t_cipher_context *ctx);
void 		des_cbc_encode(t_cipher_context *ctx);
void 		des_cbc_decode(t_cipher_context *ctx);

void		*des_cfb(t_cipher_context *ctx);
void 		des_cfb_encode(t_cipher_context *ctx);
void 		des_cfb_decode(t_cipher_context *ctx);

void		*des_ofb(t_cipher_context *ctx);
void 		des_ofb_encode(t_cipher_context *ctx);
void 		des_ofb_decode(t_cipher_context *ctx);

void		*des_ctr(t_cipher_context *ctx);
void 		des_ctr_encode(t_cipher_context *ctx);
void 		des_ctr_decode(t_cipher_context *ctx);

void		*des_3des(t_cipher_context *ctx);
void 		des_3des_encode(t_cipher_context *ctx);
void 		des_3des_decode(t_cipher_context *ctx);

/*
** des algorithm part
*/

/* beginning shuffling */

static const uint8_t	des_shfl_tbl[] = {
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7,
	56, 48, 40, 32, 24, 16, 8, 0,
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6
};

/* ending shuffling */

static const uint8_t	des_shfl_tbl_r[] = {
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25,
	32, 0, 40, 8, 48, 16, 56, 24
};

int 	des_ip_forward(LPDESBLOCK block);
int 	des_ip_reverse(LPDESBLOCK block);
int 	des_ip_debug(LPDESBLOCK block);





#endif
