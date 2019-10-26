#include "ft_ssl.h"
#include "ft_md5.h"


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
	return (buf);
}

void		print_md5(t_hash hsh, char *str, int flags)
{
	char	*out;

	if (flags & FLAG_FILEERROR)
	{
		nstrprint(
				3, "md5: ", str,
				": No such file or directory or it is directory\n"
		);
	}
	else if (flags & FLAG_Q || flags & FLAG_P)
	{
		out = nstrjoin(2, raw_md5(hsh), "\n");
		write(1, out, strlen(out));
	}
	else
	{
		if (flags & FLAG_R)
		{
			raw_md5(hsh);
			nstrprint(4,
					raw_md5(hsh),
					flags & FLAG_S ? " \"" : " ",
					str,
					flags & FLAG_S ? "\"\n" : "\n");
		}
		else
		{
			raw_md5(hsh);
			nstrprint(5,
					flags & FLAG_S ? "MD5 (\"" : "MD5 (",
					str,
					flags & FLAG_S ? "\") = " : ") = ",
					raw_md5(hsh), "\n");
		}
	}
}