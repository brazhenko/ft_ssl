#include "ft_ssl.h"

# define FUNC_F(x, y, z) ((x & y) | ((~x) & z))
# define FUNC_G(x, y, z) ((x & z) | (~z & y))
# define FUNC_H(x, y, z) (x ^ y ^ z)
# define FUNC_I(x, y, z) (y ^ (~z | x))

# define ROTATE_LEFT(x, n) (x << n | x >> (32 - n))

# define ROUND1(a, b, c, d, xk, s, i) { \
	a += FUNC_F(b, c, d) + xk + table[i-1]; \
	a = ROTATE_LEFT(a, s); \
	a += b; \
}

# define ROUND2(a, b, c, d, xk, s, i) { \
	a += FUNC_G(b, c, d) + xk + table[i-1]; \
	a = ROTATE_LEFT(a, s); \
	a += b; \
}

# define ROUND3(a, b, c, d, xk, s, i) { \
	a += FUNC_H(b, c, d) + xk + table[i-1]; \
	a = ROTATE_LEFT(a, s); \
	a += b; \
}

# define ROUND4(a, b, c, d, xk, s, i) { \
	a += FUNC_I(b, c, d) + xk + table[i-1]; \
	a = ROTATE_LEFT(a, s); \
	a += b; \
}

# define 	R1 ROUND1(hsh.a, hsh.b, hsh.c, hsh.d, buffer[0], 7, 1); \
			ROUND1(hsh.d, hsh.a, hsh.b, hsh.c, buffer[1], 12, 2); \
			ROUND1(hsh.c, hsh.d, hsh.a, hsh.b, buffer[2], 17, 3); \
			ROUND1(hsh.b, hsh.c, hsh.d, hsh.a, buffer[3], 22, 4); \
			ROUND1(hsh.a, hsh.b, hsh.c, hsh.d, buffer[4], 7, 5); \
			ROUND1(hsh.d, hsh.a, hsh.b, hsh.c, buffer[5], 12, 6); \
			ROUND1(hsh.c, hsh.d, hsh.a, hsh.b, buffer[6], 17, 7); \
			ROUND1(hsh.b, hsh.c, hsh.d, hsh.a, buffer[7], 22, 8); \
			ROUND1(hsh.a, hsh.b, hsh.c, hsh.d, buffer[8], 7, 9); \
			ROUND1(hsh.d, hsh.a, hsh.b, hsh.c, buffer[9], 12, 10); \
			ROUND1(hsh.c, hsh.d, hsh.a, hsh.b, buffer[10], 17, 11); \
			ROUND1(hsh.b, hsh.c, hsh.d, hsh.a, buffer[11], 22, 12); \
			ROUND1(hsh.a, hsh.b, hsh.c, hsh.d, buffer[12], 7, 13); \
			ROUND1(hsh.d, hsh.a, hsh.b, hsh.c, buffer[13], 12, 14); \
			ROUND1(hsh.c, hsh.d, hsh.a, hsh.b, buffer[14], 17, 15); \
			ROUND1(hsh.b, hsh.c, hsh.d, hsh.a, buffer[15], 22, 16);

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

reg32		buffer[16];

# define A 0b11111111
# define B 0b1111


char*		raw_md5(t_hash hsh)
{
	char	*buf;

	buf = (char *)malloc(33);

	buf[0] = hex_arr[hsh.a >> 4 & B];
	buf[1] = hex_arr[hsh.a >> 0 & B];
	buf[2] = hex_arr[hsh.a >> 12 & B];
	buf[3] = hex_arr[hsh.a >> 8 & B];
	buf[4] = hex_arr[hsh.a >> 20 & B];
	buf[5] = hex_arr[hsh.a >> 16 & B];
	buf[6] = hex_arr[hsh.a >> 28 & B];
	buf[7] = hex_arr[hsh.a >> 24 & B];
	//---
	buf[8] = hex_arr[hsh.b >> 4 & B];
	buf[9] = hex_arr[hsh.b >> 0 & B];
	buf[10] = hex_arr[hsh.b >> 12 & B];
	buf[11] = hex_arr[hsh.b >> 8 & B];
	buf[12] = hex_arr[hsh.b >> 20 & B];
	buf[13] = hex_arr[hsh.b >> 16 & B];
	buf[14] = hex_arr[hsh.b >> 28 & B];
	buf[15] = hex_arr[hsh.b >> 24 & B];
	//---
	buf[16] = hex_arr[hsh.c >> 4 & B];
	buf[17] = hex_arr[hsh.c >> 0 & B];
	buf[18] = hex_arr[hsh.c >> 12 & B];
	buf[19] = hex_arr[hsh.c >> 8 & B];
	buf[20] = hex_arr[hsh.c >> 20 & B];
	buf[21] = hex_arr[hsh.c >> 16 & B];
	buf[22] = hex_arr[hsh.c >> 28 & B];
	buf[23] = hex_arr[hsh.c >> 24 & B];
	//---
	buf[24] = hex_arr[hsh.d >> 4 & B];
	buf[25] = hex_arr[hsh.d >> 0 & B];
	buf[26] = hex_arr[hsh.d >> 12 & B];
	buf[27] = hex_arr[hsh.d >> 8 & B];
	buf[28] = hex_arr[hsh.d >> 20 & B];
	buf[29] = hex_arr[hsh.d >> 16 & B];
	buf[30] = hex_arr[hsh.d >> 28 & B];
	buf[31] = hex_arr[hsh.d >> 24 & B];

	buf[32] = 0;

//	printf("%02x", hsh.a >> 0 & A);
//	printf("%02x", hsh.a >> 8 & A);
//	printf("%02x", hsh.a >> 16 & A);
//	printf("%02x", hsh.a >> 24 & A);
//
//	printf("%02x", hsh.b >> 0 & A);
//	printf("%02x", hsh.b >> 8 & A);
//	printf("%02x", hsh.b >> 16 & A);
//	printf("%02x", hsh.b >> 24 & A);
//
//	printf("%02x", hsh.c >> 0 & A);
//	printf("%02x", hsh.c >> 8 & A);
//	printf("%02x", hsh.c >> 16 & A);
//	printf("%02x", hsh.c >> 24 & A);
//
//	printf("%02x", hsh.d >> 0 & A);
//	printf("%02x", hsh.d >> 8 & A);
//	printf("%02x", hsh.d >> 16 & A);
//	printf("%02x", hsh.d >> 24 & A);
//	fflush(stdout);
	return (buf);
}

void		print_md5(t_hash hsh, char *str, int flags)
{
	char	*out;

	if (flags & FLAG_Q || flags & FLAG_P)
	{
		raw_md5(hsh);
		printf("\n");
	}
	else
	{
		if (flags & FLAG_R)
		{
			raw_md5(hsh);
			out = nstrjoin(4, raw_md5(hsh),
					flags & FLAG_S ? " \"" : " ",
					str,
					flags & FLAG_S ? "\"\n" : "\n");
			write(1, out, strlen(out));
		}
		else
		{
			raw_md5(hsh);
			out = nstrjoin(5,
					flags & FLAG_S ? "MD5 (\"" : "MD5 (",
					str,
					flags & FLAG_S ? "\") = " : ") = ",
					raw_md5(hsh), "\n");
			write(1, out, strlen(out));
		}
	}
}

int			init_hash(t_hash *hash)
{
	hash->a = 0x67452301;
	hash->b = 0xEFCDAB89;
	hash->c = 0x98BADCFE;
	hash->d = 0x10325476;
	return (0);
}

int		fill_msg_len(size_t msg_len, char *buffer)
{
	buffer[56] = (msg_len * 8) >> (8 * 0) & A;
	buffer[57] = (msg_len * 8) >> (8 * 1) & A;
	buffer[58] = (msg_len * 8) >> (8 * 2) & A;
	buffer[59] = (msg_len * 8) >> (8 * 3) & A;
	buffer[60] = (msg_len * 8) >> (8 * 4) & A;
	buffer[61] = (msg_len * 8) >> (8 * 5) & A;
	buffer[62] = (msg_len * 8) >> (8 * 6) & A;
	buffer[63] = (msg_len * 8) >> (8 * 7) & A;
	return (0);
}

size_t	fill_buffer_from_str(char *str, char *buffer)
{
	static char		*str_char_ptr = NULL;
	static int		return_append_array = 0;
	static char 	append_buffer[64];
	static size_t	msg_len = 0;
	size_t			i;

	if (!str_char_ptr)
		str_char_ptr = str;
	if (return_append_array)
	{
		memcpy(buffer, append_buffer, 64);
		return_append_array = 0;
		msg_len = 0;
		bzero(append_buffer, 64);
		str_char_ptr = NULL;
	}
	i = 0;
	while (str_char_ptr[i] && i < 64)
	{
		buffer[i] = str_char_ptr[i];
		++i;
	}
	msg_len += i;
	if (i == 64)
		return (0);
	bzero(buffer + i, 64 - i);
	buffer[i] = 0x80;
	if (i >= 56)
	{
		bzero(append_buffer, 64);
		fill_msg_len(msg_len, append_buffer);
		return_append_array = 1;
		return (0);
	}
	else
	{
		fill_msg_len(msg_len, buffer);
		return_append_array = 0;
		msg_len = 0;
		bzero(append_buffer, 64);
		str_char_ptr = NULL;
		return (1);
	}
}

size_t	fill_buffer_from_stream(int fd, char *buffer)
{
	static char			append_buffer[64];
	static int			return_append_array = 0;
	static size_t		msg_len = 0;
	size_t				read_len;

	if (return_append_array == 1)
	{
		memcpy(buffer, append_buffer, 64);
		close(fd);
		return_append_array = 0;
		msg_len = 0;
		bzero(append_buffer, 64);
		return (1);
	}
	read_len = read(fd, buffer, MD5_BUFFER_SIZE);
	msg_len += read_len;
	if (read_len == 64)
		return (0);
	else
	{
		bzero(buffer + read_len, 64 - read_len);
		buffer[read_len] = 0x80;
		if (read_len >= 56)
		{
			bzero(append_buffer, 64);
			fill_msg_len(msg_len, append_buffer);
			return_append_array = 1;
			return (0);
		}
		else
		{
			fill_msg_len(msg_len, buffer);
			close(fd);
			return_append_array = 0;
			msg_len = 0;
			bzero(append_buffer, 64);
			return (1);
		}
	}
}

int 	fill_buffer(char *str, char *buffer, int flags)
{
	static int	file_fd = 0;

	if (flags & FLAG_S)
	{
		return (fill_buffer_from_str(str, buffer));
	}
	else if (flags & FLAG_P)
	{
		return (fill_buffer_from_stream(0, buffer));
	}
	else
	{
		if (!file_fd)
			file_fd = open(str, O_RDONLY);
		return (fill_buffer_from_stream(file_fd, buffer));
	}
}

void		*md5(char *str, int flags)
{
	t_hash		hsh;
	int			fb_return;

	init_hash(&hsh);
	bzero(buffer, 64);
	while (1)
	{
		hsh.aa = hsh.a;
		hsh.bb = hsh.b;
		hsh.cc = hsh.c;
		hsh.dd = hsh.d;

		fb_return = fill_buffer(str, (char *)buffer, flags);

		/* _________1_________ */

		ROUND1(hsh.a, hsh.b, hsh.c, hsh.d, buffer[0], 7, 1);
		ROUND1(hsh.d, hsh.a, hsh.b, hsh.c, buffer[1], 12, 2);
		ROUND1(hsh.c, hsh.d, hsh.a, hsh.b, buffer[2], 17, 3);
		ROUND1(hsh.b, hsh.c, hsh.d, hsh.a, buffer[3], 22, 4);
		ROUND1(hsh.a, hsh.b, hsh.c, hsh.d, buffer[4], 7, 5);
		ROUND1(hsh.d, hsh.a, hsh.b, hsh.c, buffer[5], 12, 6);
		ROUND1(hsh.c, hsh.d, hsh.a, hsh.b, buffer[6], 17, 7);
		ROUND1(hsh.b, hsh.c, hsh.d, hsh.a, buffer[7], 22, 8);
		ROUND1(hsh.a, hsh.b, hsh.c, hsh.d, buffer[8], 7, 9);
		ROUND1(hsh.d, hsh.a, hsh.b, hsh.c, buffer[9], 12, 10);
		ROUND1(hsh.c, hsh.d, hsh.a, hsh.b, buffer[10], 17, 11);
		ROUND1(hsh.b, hsh.c, hsh.d, hsh.a, buffer[11], 22, 12);
		ROUND1(hsh.a, hsh.b, hsh.c, hsh.d, buffer[12], 7, 13);
		ROUND1(hsh.d, hsh.a, hsh.b, hsh.c, buffer[13], 12, 14);
		ROUND1(hsh.c, hsh.d, hsh.a, hsh.b, buffer[14], 17, 15);
		ROUND1(hsh.b, hsh.c, hsh.d, hsh.a, buffer[15], 22, 16);

		/* ________2_________ */

		ROUND2(hsh.a, hsh.b, hsh.c, hsh.d, buffer[1], 5, 17);
		ROUND2(hsh.d, hsh.a, hsh.b, hsh.c, buffer[6], 9, 18);
		ROUND2(hsh.c, hsh.d, hsh.a, hsh.b, buffer[11], 14, 19);
		ROUND2(hsh.b, hsh.c, hsh.d, hsh.a, buffer[0], 20, 20);
		ROUND2(hsh.a, hsh.b, hsh.c, hsh.d, buffer[5], 5, 21);
		ROUND2(hsh.d, hsh.a, hsh.b, hsh.c, buffer[10], 9, 22);
		ROUND2(hsh.c, hsh.d, hsh.a, hsh.b, buffer[15], 14, 23);
		ROUND2(hsh.b, hsh.c, hsh.d, hsh.a, buffer[4], 20, 24);
		ROUND2(hsh.a, hsh.b, hsh.c, hsh.d, buffer[9], 5, 25);
		ROUND2(hsh.d, hsh.a, hsh.b, hsh.c, buffer[14], 9, 26);
		ROUND2(hsh.c, hsh.d, hsh.a, hsh.b, buffer[3], 14, 27);
		ROUND2(hsh.b, hsh.c, hsh.d, hsh.a, buffer[8], 20, 28);
		ROUND2(hsh.a, hsh.b, hsh.c, hsh.d, buffer[13], 5, 29);
		ROUND2(hsh.d, hsh.a, hsh.b, hsh.c, buffer[2], 9, 30);
		ROUND2(hsh.c, hsh.d, hsh.a, hsh.b, buffer[7], 14, 31);
		ROUND2(hsh.b, hsh.c, hsh.d, hsh.a, buffer[12], 20, 32);

		/* ________3_________ */

		ROUND3(hsh.a, hsh.b, hsh.c, hsh.d, buffer[5], 4, 33);
		ROUND3(hsh.d, hsh.a, hsh.b, hsh.c, buffer[8], 11, 34);
		ROUND3(hsh.c, hsh.d, hsh.a, hsh.b, buffer[11], 16, 35);
		ROUND3(hsh.b, hsh.c, hsh.d, hsh.a, buffer[14], 23, 36);
		ROUND3(hsh.a, hsh.b, hsh.c, hsh.d, buffer[1], 4, 37);
		ROUND3(hsh.d, hsh.a, hsh.b, hsh.c, buffer[4], 11, 38);
		ROUND3(hsh.c, hsh.d, hsh.a, hsh.b, buffer[7], 16, 39);
		ROUND3(hsh.b, hsh.c, hsh.d, hsh.a, buffer[10], 23, 40);
		ROUND3(hsh.a, hsh.b, hsh.c, hsh.d, buffer[13], 4, 41);
		ROUND3(hsh.d, hsh.a, hsh.b, hsh.c, buffer[0], 11, 42);
		ROUND3(hsh.c, hsh.d, hsh.a, hsh.b, buffer[3], 16, 43);
		ROUND3(hsh.b, hsh.c, hsh.d, hsh.a, buffer[6], 23, 44);
		ROUND3(hsh.a, hsh.b, hsh.c, hsh.d, buffer[9], 4, 45);
		ROUND3(hsh.d, hsh.a, hsh.b, hsh.c, buffer[12], 11, 46);
		ROUND3(hsh.c, hsh.d, hsh.a, hsh.b, buffer[15], 16, 47);
		ROUND3(hsh.b, hsh.c, hsh.d, hsh.a, buffer[2], 23, 48);

		/* ________4_________ */

		ROUND4(hsh.a, hsh.b, hsh.c, hsh.d, buffer[0], 6, 49);
		ROUND4(hsh.d, hsh.a, hsh.b, hsh.c, buffer[7], 10, 50);
		ROUND4(hsh.c, hsh.d, hsh.a, hsh.b, buffer[14], 15, 51);
		ROUND4(hsh.b, hsh.c, hsh.d, hsh.a, buffer[5], 21, 52);
		ROUND4(hsh.a, hsh.b, hsh.c, hsh.d, buffer[12], 6, 53);
		ROUND4(hsh.d, hsh.a, hsh.b, hsh.c, buffer[3], 10, 54);
		ROUND4(hsh.c, hsh.d, hsh.a, hsh.b, buffer[10], 15, 55);
		ROUND4(hsh.b, hsh.c, hsh.d, hsh.a, buffer[1], 21, 56);
		ROUND4(hsh.a, hsh.b, hsh.c, hsh.d, buffer[8], 6, 57);
		ROUND4(hsh.d, hsh.a, hsh.b, hsh.c, buffer[15], 10, 58);
		ROUND4(hsh.c, hsh.d, hsh.a, hsh.b, buffer[6], 15, 59);
		ROUND4(hsh.b, hsh.c, hsh.d, hsh.a, buffer[13], 21, 60);
		ROUND4(hsh.a, hsh.b, hsh.c, hsh.d, buffer[4], 6, 61);
		ROUND4(hsh.d, hsh.a, hsh.b, hsh.c, buffer[11], 10, 62);
		ROUND4(hsh.c, hsh.d, hsh.a, hsh.b, buffer[2], 15, 63);
		ROUND4(hsh.b, hsh.c, hsh.d, hsh.a, buffer[9], 21, 64);

		hsh.a += hsh.aa;
		hsh.b += hsh.bb;
		hsh.c += hsh.cc;
		hsh.d += hsh.dd;
		if (fb_return)
			break ;
	}
	print_md5(hsh, str, flags);
	return (NULL);
}
