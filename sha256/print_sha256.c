#include "sha256.h"
#include "ssl.h"
#include <stdio.h>
#include "utilities.h"

/*
**	Returns fresh allocated string with ascii printable hash.
**
*/

char			*sha256toa(t_hash_sha256 hash)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(65);
	i = 0;
	bzero(str, 65);
	while (i < 8)
	{
		str[8 * i + 0] = hex_arr[((hash.hash[i] >> 28) & 0b1111)];
		str[8 * i + 1] = hex_arr[((hash.hash[i] >> 24) & 0b1111)];
		str[8 * i + 2] = hex_arr[((hash.hash[i] >> 20) & 0b1111)];
		str[8 * i + 3] = hex_arr[((hash.hash[i] >> 16) & 0b1111)];
		str[8 * i + 4] = hex_arr[((hash.hash[i] >> 12) & 0b1111)];
		str[8 * i + 5] = hex_arr[((hash.hash[i] >> 8) & 0b1111)];
		str[8 * i + 6] = hex_arr[((hash.hash[i] >> 4) & 0b1111)];
		str[8 * i + 7] = hex_arr[((hash.hash[i] >> 0) & 0b1111)];
		i++;
	}
	return (str);
}

void			print_sha256_hash(t_hash_sha256 hash, char *str, int flags)
{
	char	*sha256_hash_string;

	sha256_hash_string = sha256toa(hash);
	if (hash.error == 1)
		nstrprint(3, "sha256: ", str, ": Is a directory\n");
	else if (flags & FLAG_P)
		nstrprint(1, str, sha256_hash_string);
	else if (flags & FLAG_Q || flags & FLAG_STDIN)
		nstrprint(2, sha256_hash_string, "\n");
	else if (flags & FLAG_R)
		nstrprint(5, sha256_hash_string,
				(flags & FLAG_S) ? " \"" : " ",
				str,
				(flags & FLAG_S) ? "\"" : "", "\n");
	else
		nstrprint(6, "SHA256",
				(flags & FLAG_S) ? " (\"" : " (",
				str,
				(flags & FLAG_S) ? "\") = " : ") = ",
				sha256_hash_string, "\n");
	free(sha256_hash_string);
}
