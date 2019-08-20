#include "ft_ssl.h"

typedef uint32_t 		reg32;
typedef unsigned char	byte;

typedef struct
{
	reg32	a;
	reg32	b;
	reg32	c;
	reg32	d;
	reg32	aa;
	reg32	bb;
	reg32	cc;
	reg32	dd;
}						t_hash;

const unsigned table[64] = {
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

size_t		clcl_new_len(size_t orig_len)
{
	size_t		new_len;

	new_len = orig_len;
	++new_len;	
	while (new_len % 64 != 56)
	{
		++new_len;
	}
	while (new_len % 64 != 0)
	{
		++new_len;
	}
	return (new_len);
}


byte		*memory_append(const char *str, size_t orig_len)
{
	byte	*new;

	size_t		new_len;

	new_len = clcl_new_len(orig_len);
	// printf("Orig len: %lu\nNew len: %lu Block count: %lu\n", orig_len, new_len, new_len / 64);
	new = malloc(new_len);
	memcpy(new, str, orig_len);
	return (new);
}

byte		*cat_padding(byte *arr, size_t orig_len)
{
	arr[orig_len] = 0x80;
	bzero(&arr[orig_len + 1], clcl_new_len(orig_len) - orig_len - 1);
	return (arr);
}

# define A 0b11111111

byte		*cat_length(byte *arr, size_t orig_len)
{
	size_t		i;

	i = clcl_new_len(orig_len) - 8;
	
	// printf("index: %lu\n", i);

	arr[i + 0] = (orig_len * 8) >> (8 * 0) & A;
	arr[i + 1] = (orig_len * 8) >> (8 * 1) & A;
	arr[i + 2] = (orig_len * 8) >> (8 * 2) & A;
	arr[i + 3] = (orig_len * 8) >> (8 * 3) & A;
	
	arr[i + 4] = (orig_len * 8) >> (8 * 4) & A;
	arr[i + 5] = (orig_len * 8) >> (8 * 5) & A;
	arr[i + 6] = (orig_len * 8) >> (8 * 6) & A;
	arr[i + 7] = (orig_len * 8) >> (8 * 7) & A;
	
	return (arr);
}

int			init_buffer(t_hash *hash)
{
	hash->a = 0x67452301;
	hash->b = 0xEFCDAB89;
	hash->c = 0x98BADCFE;
	hash->d = 0x10325476;

	return (0);
}



# define FUNC_F(x, y, z) ((x & y) | ((~x) & z))
# define FUNC_G(x, y, z) ((x & z) | (~z & y))
# define FUNC_H(x, y, z) (x ^ y ^ z)
# define FUNC_I(x, y, z) (y ^ (~z | x))

reg32	f1(reg32 x, reg32 y, reg32 z)
{
	return ((x & y) | ((~x) & z));
}

reg32	g1(reg32 x, reg32 y, reg32 z)
{
	return (x & z) | (~z & y);
}

reg32	h1(reg32 x, reg32 y, reg32 z)
{
	return (x ^ y ^ z);
}

reg32	i1(reg32 x, reg32 y, reg32 z)
{
	return (y ^ (~z | x));
}
// # define ROUND1(a, b, c, d, func, x, k, s, i) (b + (((a + func(b, c, d) + x[k] + table[i-1]) << s) | ((a + func(b, c, d) + x[k] + table[i-1]) >> (32 - s))))
t_hash		hsh;

reg32		ROUND(reg32 a, reg32 b, reg32 c, reg32 d,
					reg32 (*func) (reg32, reg32, reg32),
					reg32 x[16], reg32 k, reg32 s, reg32 i)
{
	reg32 tmp;

	tmp = (a + func(b, c, d) + x[k] + table[i-1]);
	return (b + ((tmp << s) | (tmp >> (32 - s))));
}

void		*md5(const char *str)
{

	size_t		orig_len;
	reg32		*new;
	reg32		copy[16];

	orig_len = strlen(str);	
	new = (reg32 *)memory_append(str, orig_len);
	new = (reg32 *)cat_padding((byte *)new, orig_len);
	new = (reg32 *)cat_length((byte *)new, orig_len);
	init_buffer(&hsh);

	for (size_t i = 0; i < clcl_new_len(orig_len) / 64; ++i)
	{
		for (size_t j = 0; j < 16; ++j)
		{
			copy[j] = new[i * 16 + j];
		}

		hsh.aa = hsh.a;
		hsh.bb = hsh.b;
		hsh.cc = hsh.c;
		hsh.dd = hsh.d;

		/* _________1_________ */

		hsh.a = ROUND(hsh.a, hsh.b, hsh.c, hsh.d, f1, copy, 0, 7, 1);
		hsh.d = ROUND(hsh.d, hsh.a, hsh.b, hsh.c, f1, copy, 1, 12, 2);
		hsh.c = ROUND(hsh.c, hsh.d, hsh.a, hsh.b, f1, copy, 2, 17, 3);
		hsh.b = ROUND(hsh.b, hsh.c, hsh.d, hsh.a, f1, copy, 3, 22, 4);
		hsh.a = ROUND(hsh.a, hsh.b, hsh.c, hsh.d, f1, copy, 4, 7, 5);
		hsh.d = ROUND(hsh.d, hsh.a, hsh.b, hsh.c, f1, copy, 5, 12, 6);
		hsh.c = ROUND(hsh.c, hsh.d, hsh.a, hsh.b, f1, copy, 6, 17, 7);
		hsh.b = ROUND(hsh.b, hsh.c, hsh.d, hsh.a, f1, copy, 7, 22, 8);
		hsh.a = ROUND(hsh.a, hsh.b, hsh.c, hsh.d, f1, copy, 8, 7, 9);
		hsh.d = ROUND(hsh.d, hsh.a, hsh.b, hsh.c, f1, copy, 9, 12, 10);
		hsh.c = ROUND(hsh.c, hsh.d, hsh.a, hsh.b, f1, copy, 10, 17, 11);
		hsh.b = ROUND(hsh.b, hsh.c, hsh.d, hsh.a, f1, copy, 11, 22, 12);
		hsh.a = ROUND(hsh.a, hsh.b, hsh.c, hsh.d, f1, copy, 12, 7, 13);
		hsh.d = ROUND(hsh.d, hsh.a, hsh.b, hsh.c, f1, copy, 13, 12, 14);
		hsh.c = ROUND(hsh.c, hsh.d, hsh.a, hsh.b, f1, copy, 14, 17, 15);
		hsh.b = ROUND(hsh.b, hsh.c, hsh.d, hsh.a, f1, copy, 15, 22, 16);

		/* ________2_________ */
		
		hsh.a = ROUND(hsh.a, hsh.b, hsh.c, hsh.d, g1, copy, 1, 5, 17);
		hsh.d = ROUND(hsh.d, hsh.a, hsh.b, hsh.c, g1, copy, 6, 9, 18);
		hsh.c = ROUND(hsh.c, hsh.d, hsh.a, hsh.b, g1, copy, 11, 14, 19);
		hsh.b = ROUND(hsh.b, hsh.c, hsh.d, hsh.a, g1, copy, 0, 20, 20);
		hsh.a = ROUND(hsh.a, hsh.b, hsh.c, hsh.d, g1, copy, 5, 5, 21);
		hsh.d = ROUND(hsh.d, hsh.a, hsh.b, hsh.c, g1, copy, 10, 9, 22);
		hsh.c = ROUND(hsh.c, hsh.d, hsh.a, hsh.b, g1, copy, 15, 14, 23);
		hsh.b = ROUND(hsh.b, hsh.c, hsh.d, hsh.a, g1, copy, 4, 20, 24);
		hsh.a = ROUND(hsh.a, hsh.b, hsh.c, hsh.d, g1, copy, 9, 5, 25);
		hsh.d = ROUND(hsh.d, hsh.a, hsh.b, hsh.c, g1, copy, 14, 9, 26);
		hsh.c = ROUND(hsh.c, hsh.d, hsh.a, hsh.b, g1, copy, 3, 14, 27);
		hsh.b = ROUND(hsh.b, hsh.c, hsh.d, hsh.a, g1, copy, 8, 20, 28);
		hsh.a = ROUND(hsh.a, hsh.b, hsh.c, hsh.d, g1, copy, 13, 5, 29);
		hsh.d = ROUND(hsh.d, hsh.a, hsh.b, hsh.c, g1, copy, 2, 9, 30);
		hsh.c = ROUND(hsh.c, hsh.d, hsh.a, hsh.b, g1, copy, 7, 14, 31);
		hsh.b = ROUND(hsh.b, hsh.c, hsh.d, hsh.a, g1, copy, 12, 20, 32);

		/* ________3_________ */

		hsh.a = ROUND(hsh.a, hsh.b, hsh.c, hsh.d, h1, copy, 5, 4, 33);
		hsh.d = ROUND(hsh.d, hsh.a, hsh.b, hsh.c, h1, copy, 8, 11, 34);
		hsh.c = ROUND(hsh.c, hsh.d, hsh.a, hsh.b, h1, copy, 11, 16, 35);
		hsh.b = ROUND(hsh.b, hsh.c, hsh.d, hsh.a, h1, copy, 14, 23, 36);
		hsh.a = ROUND(hsh.a, hsh.b, hsh.c, hsh.d, h1, copy, 1, 4, 37);
		hsh.d = ROUND(hsh.d, hsh.a, hsh.b, hsh.c, h1, copy, 4, 11, 38);
		hsh.c = ROUND(hsh.c, hsh.d, hsh.a, hsh.b, h1, copy, 7, 16, 39);
		hsh.b = ROUND(hsh.b, hsh.c, hsh.d, hsh.a, h1, copy, 10, 23, 40);
		hsh.a = ROUND(hsh.a, hsh.b, hsh.c, hsh.d, h1, copy, 13, 4, 41);
		hsh.d = ROUND(hsh.d, hsh.a, hsh.b, hsh.c, h1, copy, 0, 11, 42);
		hsh.c = ROUND(hsh.c, hsh.d, hsh.a, hsh.b, h1, copy, 3, 16, 43);
		hsh.b = ROUND(hsh.b, hsh.c, hsh.d, hsh.a, h1, copy, 6, 23, 44);
		hsh.a = ROUND(hsh.a, hsh.b, hsh.c, hsh.d, h1, copy, 9, 4, 45);
		hsh.d = ROUND(hsh.d, hsh.a, hsh.b, hsh.c, h1, copy, 12, 11, 46);
		hsh.c = ROUND(hsh.c, hsh.d, hsh.a, hsh.b, h1, copy, 15, 16, 47);
		hsh.b = ROUND(hsh.b, hsh.c, hsh.d, hsh.a, h1, copy, 2, 23, 48);

		/* ________4_________ */

		hsh.a = ROUND(hsh.a, hsh.b, hsh.c, hsh.d, i1, copy, 0, 6, 49);
		hsh.d = ROUND(hsh.d, hsh.a, hsh.b, hsh.c, i1, copy, 7, 10, 50);
		hsh.c = ROUND(hsh.c, hsh.d, hsh.a, hsh.b, i1, copy, 14, 15, 51);
		hsh.b = ROUND(hsh.b, hsh.c, hsh.d, hsh.a, i1, copy, 5, 21, 52);
		hsh.a = ROUND(hsh.a, hsh.b, hsh.c, hsh.d, i1, copy, 12, 6, 53);
		hsh.d = ROUND(hsh.d, hsh.a, hsh.b, hsh.c, i1, copy, 3, 10, 54);
		hsh.c = ROUND(hsh.c, hsh.d, hsh.a, hsh.b, i1, copy, 10, 15, 55);
		hsh.b = ROUND(hsh.b, hsh.c, hsh.d, hsh.a, i1, copy, 1, 21, 56);
		hsh.a = ROUND(hsh.a, hsh.b, hsh.c, hsh.d, i1, copy, 8, 6, 57);
		hsh.d = ROUND(hsh.d, hsh.a, hsh.b, hsh.c, i1, copy, 15, 10, 58);
		hsh.c = ROUND(hsh.c, hsh.d, hsh.a, hsh.b, i1, copy, 6, 15, 59);
		hsh.b = ROUND(hsh.b, hsh.c, hsh.d, hsh.a, i1, copy, 13, 21, 60);
		hsh.a = ROUND(hsh.a, hsh.b, hsh.c, hsh.d, i1, copy, 4, 6, 61);
		hsh.d = ROUND(hsh.d, hsh.a, hsh.b, hsh.c, i1, copy, 11, 10, 62);
		hsh.c = ROUND(hsh.c, hsh.d, hsh.a, hsh.b, i1, copy, 2, 15, 63);
		hsh.b = ROUND(hsh.b, hsh.c, hsh.d, hsh.a, i1, copy, 9, 21, 64);

		hsh.a += hsh.aa;
		hsh.b += hsh.bb;
		hsh.c += hsh.cc;
		hsh.d += hsh.dd;
	}

	printf("%02x", hsh.a >> 0 & A);
	printf("%02x", hsh.a >> 8 & A);
	printf("%02x", hsh.a >> 16 & A);
	printf("%02x", hsh.a >> 24 & A);

	printf("%02x", hsh.b >> 0 & A);
	printf("%02x", hsh.b >> 8 & A);
	printf("%02x", hsh.b >> 16 & A);
	printf("%02x", hsh.b >> 24 & A);

	printf("%02x", hsh.c >> 0 & A);
	printf("%02x", hsh.c >> 8 & A);
	printf("%02x", hsh.c >> 16 & A);
	printf("%02x", hsh.c >> 24 & A);

	printf("%02x", hsh.d >> 0 & A);
	printf("%02x", hsh.d >> 8 & A);
	printf("%02x", hsh.d >> 16 & A);
	printf("%02x\n", hsh.d >> 24 & A);

	return (NULL);
}
