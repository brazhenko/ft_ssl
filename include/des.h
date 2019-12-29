#ifndef DES_H
#define DES_H

# include <stdint.h>
# include "cipher_context.h"
# include <limits.h>
# include <unistd.h>

# define DES_CIPHER_BLOCK_LEN	(64/(CHAR_BIT))
# define DES_CIPHER_BIT_LEN		(64)

typedef		uint8_t				DESBLOCK[8];
typedef		DESBLOCK			*LPDESBLOCK;
typedef		uint8_t 			DESHALFBLOCK[4];
typedef		DESHALFBLOCK		*LPDESHALFBLOCK;
typedef		uint8_t				DES64KEY[8];
typedef		DES64KEY			*LPDES64KEY;
typedef		uint8_t				DES56KEY[7];
typedef		DES56KEY			*LPDES56KEY;
typedef		uint8_t				DES48KEY[6];
typedef		DES48KEY			*LPDES48KEY;

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

/* Des half block spread table */

static const uint8_t	des_e_tbl[] = {
	31, 0, 1, 2, 3, 4, 3, 4,
	5, 6, 7, 8, 7, 8, 9, 10,
	11, 12, 11, 12, 13, 14, 15, 16,
	15, 16, 17, 18, 19, 20, 19, 20,
	21, 22, 23, 24, 23, 24, 25, 26,
	27, 28, 27, 28, 29, 30, 31, 0
};

/* table P */

static const uint8_t	des_p_tbl[] = {
	15, 6, 19, 20, 28, 11, 27, 16,
	0, 14, 22, 25, 4, 17, 30, 9,
	1, 7, 23, 13, 31, 26, 2, 8,
	18, 12, 29, 5, 21, 10, 3, 24
};

/* round key compress and shuffle table */

static const uint8_t	cmprs_key[] = {
	56, 48, 40, 32, 24, 16, 8, 0,
	57, 49, 41, 33, 25, 17, 9, 1,
	58, 50, 42, 34, 26, 18, 10, 2,
	59, 51, 43, 35, 62, 54, 46, 38,
	30, 22, 14, 6, 61, 53, 45, 37,
	29, 21, 13, 5, 60, 52, 44, 36,
	28, 20, 12, 4, 27, 19, 11, 3
};

int 	des_permute_key1(LPDES64KEY key);


/* key round padding */

static const uint8_t 	des_key_pd[] = {
	1, 1, 2, 2, 2, 2, 2, 2,
	1, 2, 2, 2, 2, 2, 2, 1
};

#endif
