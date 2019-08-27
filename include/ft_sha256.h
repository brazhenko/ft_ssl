#ifndef FT_SHA256_H
#define FT_SHA256_H

# define SHA256_BLOCK_SIZE 64 // 512 bit blocks
# define SHA256_WORD_SIZE 4 // 32-bit words

# define CH_256(x, y, z) {(x & y) ^ ( (~x) & z)}
# define MAJ_256(x, y, z) {(x & y) ^ (x & z) ^ (y & z)}

# define BSIG0_256(x) {ROTR^2(x) ^ ROTR^13(x) ^ ROTR^22(x)}
# define BSIG1_256(x) {ROTR^6(x) ^ ROTR^11(x) ^ ROTR^25(x)}
# define SSIG0_256(x) {ROTR^7(x) ^ ROTR^18(x) ^ SHR^3(x)}
# define SSIG1_256(x) {ROTR^17(x) ^ ROTR^19(x) ^ SHR^10(x)}

typedef struct
{
	reg32	hash[8];
}				t_hash_sha256;

#endif
