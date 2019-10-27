#ifndef FT_MD5_H
# define FT_MD5_H

# define MD5_BUFFER_SIZE 512

# define FUNC_F(x, y, z) ((x & y) | ((~x) & z))
# define FUNC_G(x, y, z) ((x & z) | (~z & y))
# define FUNC_H(x, y, z) (x ^ y ^ z)
# define FUNC_I(x, y, z) (y ^ (~z | x))

# define LROT(x, n) (x << n | x >> (32 - n))

# define ROUND1(a, b, c, d, xk, s, i) { \
	a += FUNC_F(b, c, d) + xk + table[i-1]; \
	a = LROT(a, s); \
	a += b; \
}

# define ROUND2(a, b, c, d, xk, s, i) { \
	a += FUNC_G(b, c, d) + xk + table[i-1]; \
	a = LROT(a, s); \
	a += b; \
}

# define ROUND3(a, b, c, d, xk, s, i) { \
	a += FUNC_H(b, c, d) + xk + table[i-1]; \
	a = LROT(a, s); \
	a += b; \
}

# define ROUND4(a, b, c, d, xk, s, i) { \
	a += FUNC_I(b, c, d) + xk + table[i-1]; \
	a = LROT(a, s); \
	a += b; \
}

# define R1 ROUND1(hash.a, hash.b, hash.c, hash.d, buffer[0], 7, 1); \
			ROUND1(hash.d, hash.a, hash.b, hash.c, buffer[1], 12, 2); \
			ROUND1(hash.c, hash.d, hash.a, hash.b, buffer[2], 17, 3); \
			ROUND1(hash.b, hash.c, hash.d, hash.a, buffer[3], 22, 4); \
			ROUND1(hash.a, hash.b, hash.c, hash.d, buffer[4], 7, 5); \
			ROUND1(hash.d, hash.a, hash.b, hash.c, buffer[5], 12, 6); \
			ROUND1(hash.c, hash.d, hash.a, hash.b, buffer[6], 17, 7); \
			ROUND1(hash.b, hash.c, hash.d, hash.a, buffer[7], 22, 8); \
			ROUND1(hash.a, hash.b, hash.c, hash.d, buffer[8], 7, 9); \
			ROUND1(hash.d, hash.a, hash.b, hash.c, buffer[9], 12, 10); \
			ROUND1(hash.c, hash.d, hash.a, hash.b, buffer[10], 17, 11); \
			ROUND1(hash.b, hash.c, hash.d, hash.a, buffer[11], 22, 12); \
			ROUND1(hash.a, hash.b, hash.c, hash.d, buffer[12], 7, 13); \
			ROUND1(hash.d, hash.a, hash.b, hash.c, buffer[13], 12, 14); \
			ROUND1(hash.c, hash.d, hash.a, hash.b, buffer[14], 17, 15); \
			ROUND1(hash.b, hash.c, hash.d, hash.a, buffer[15], 22, 16);

# define R2	ROUND2(hash.a, hash.b, hash.c, hash.d, buffer[1], 5, 17); \
			ROUND2(hash.d, hash.a, hash.b, hash.c, buffer[6], 9, 18); \
			ROUND2(hash.c, hash.d, hash.a, hash.b, buffer[11], 14, 19); \
			ROUND2(hash.b, hash.c, hash.d, hash.a, buffer[0], 20, 20); \
			ROUND2(hash.a, hash.b, hash.c, hash.d, buffer[5], 5, 21); \
			ROUND2(hash.d, hash.a, hash.b, hash.c, buffer[10], 9, 22); \
			ROUND2(hash.c, hash.d, hash.a, hash.b, buffer[15], 14, 23); \
			ROUND2(hash.b, hash.c, hash.d, hash.a, buffer[4], 20, 24); \
			ROUND2(hash.a, hash.b, hash.c, hash.d, buffer[9], 5, 25); \
			ROUND2(hash.d, hash.a, hash.b, hash.c, buffer[14], 9, 26); \
			ROUND2(hash.c, hash.d, hash.a, hash.b, buffer[3], 14, 27); \
			ROUND2(hash.b, hash.c, hash.d, hash.a, buffer[8], 20, 28); \
			ROUND2(hash.a, hash.b, hash.c, hash.d, buffer[13], 5, 29); \
			ROUND2(hash.d, hash.a, hash.b, hash.c, buffer[2], 9, 30); \
			ROUND2(hash.c, hash.d, hash.a, hash.b, buffer[7], 14, 31); \
			ROUND2(hash.b, hash.c, hash.d, hash.a, buffer[12], 20, 32);

# define R3	ROUND3(hash.a, hash.b, hash.c, hash.d, buffer[5], 4, 33); \
			ROUND3(hash.d, hash.a, hash.b, hash.c, buffer[8], 11, 34); \
			ROUND3(hash.c, hash.d, hash.a, hash.b, buffer[11], 16, 35); \
			ROUND3(hash.b, hash.c, hash.d, hash.a, buffer[14], 23, 36); \
			ROUND3(hash.a, hash.b, hash.c, hash.d, buffer[1], 4, 37); \
			ROUND3(hash.d, hash.a, hash.b, hash.c, buffer[4], 11, 38); \
			ROUND3(hash.c, hash.d, hash.a, hash.b, buffer[7], 16, 39); \
			ROUND3(hash.b, hash.c, hash.d, hash.a, buffer[10], 23, 40); \
			ROUND3(hash.a, hash.b, hash.c, hash.d, buffer[13], 4, 41); \
			ROUND3(hash.d, hash.a, hash.b, hash.c, buffer[0], 11, 42); \
			ROUND3(hash.c, hash.d, hash.a, hash.b, buffer[3], 16, 43); \
			ROUND3(hash.b, hash.c, hash.d, hash.a, buffer[6], 23, 44); \
			ROUND3(hash.a, hash.b, hash.c, hash.d, buffer[9], 4, 45); \
			ROUND3(hash.d, hash.a, hash.b, hash.c, buffer[12], 11, 46); \
			ROUND3(hash.c, hash.d, hash.a, hash.b, buffer[15], 16, 47); \
			ROUND3(hash.b, hash.c, hash.d, hash.a, buffer[2], 23, 48);


# define R4	ROUND4(hash.a, hash.b, hash.c, hash.d, buffer[0], 6, 49); \
			ROUND4(hash.d, hash.a, hash.b, hash.c, buffer[7], 10, 50); \
			ROUND4(hash.c, hash.d, hash.a, hash.b, buffer[14], 15, 51); \
			ROUND4(hash.b, hash.c, hash.d, hash.a, buffer[5], 21, 52); \
			ROUND4(hash.a, hash.b, hash.c, hash.d, buffer[12], 6, 53); \
			ROUND4(hash.d, hash.a, hash.b, hash.c, buffer[3], 10, 54); \
			ROUND4(hash.c, hash.d, hash.a, hash.b, buffer[10], 15, 55); \
			ROUND4(hash.b, hash.c, hash.d, hash.a, buffer[1], 21, 56); \
			ROUND4(hash.a, hash.b, hash.c, hash.d, buffer[8], 6, 57); \
			ROUND4(hash.d, hash.a, hash.b, hash.c, buffer[15], 10, 58); \
			ROUND4(hash.c, hash.d, hash.a, hash.b, buffer[6], 15, 59); \
			ROUND4(hash.b, hash.c, hash.d, hash.a, buffer[13], 21, 60); \
			ROUND4(hash.a, hash.b, hash.c, hash.d, buffer[4], 6, 61); \
			ROUND4(hash.d, hash.a, hash.b, hash.c, buffer[11], 10, 62); \
			ROUND4(hash.c, hash.d, hash.a, hash.b, buffer[2], 15, 63); \
			ROUND4(hash.b, hash.c, hash.d, hash.a, buffer[9], 21, 64);


static const unsigned table[64] = {
							3614090360, 3905402710, 606105819, 3250441966,
							4118548399, 1200080426, 2821735955, 4249261313,
							1770035416, 2336552879, 4294925233, 2304563134,
							1804603682, 4254626195, 2792965006, 1236535329,
							4129170786, 3225465664, 643717713, 3921069994,
							3593408605, 38016083, 3634488961, 3889429448,
							568446438, 3275163606, 4107603335, 1163531501,
							2850285829, 4243563512, 1735328473, 2368359562,
							4294588738, 2272392833, 1839030562, 4259657740,
							2763975236, 1272893353, 4139469664, 3200236656,
							681279174, 3936430074, 3572445317, 76029189,
							3654602809, 3873151461, 530742520, 3299628645,
							4096336452, 1126891415, 2878612391, 4237533241,
							1700485571, 2399980690, 4293915773, 2240044497,
							1873313359, 4264355552, 2734768916, 1309151649,
							4149444226, 3174756917, 718787259, 3951481745,
};

# define A 0b11111111
# define B 0b1111


void		*md5(char *str, int flags);

#endif
