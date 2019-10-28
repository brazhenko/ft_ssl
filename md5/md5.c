#include "md5.h"

// TODO decide the arcitecture of buffer


int			init_md5_hash(t_hash_md5 *hash)
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

void		*md5(char *str, int flags)
{

	t_hash_md5		hash;

	init_md5_hash(&hash);
	if (flags & FLAG_P || flags & FLAG_STDIN)
		hash = calculate_md5_from_stdin();
	else if (flags & FLAG_S)
		hash = calculate_md5_from_string(str);
	else
		hash = calculate_md5_from_file(str);
	print_md5(hash, str, flags);
	return (NULL);
}