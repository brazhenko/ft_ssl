/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_md5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:22:08 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/28 23:22:10 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "md5.h"

/*
**		Honest hardcode to translate md5 to ascii,
** 		something went wrong during algo so need to fix it like that.
*/

static const int	g_tbl[] = {
	4, 0, 12, 8, 20, 16, 28, 24
};

char		*raw_md5(t_hash_md5 hsh)
{
	char	*buf;
	int		i;

	buf = (char *)malloc(33);
	i = 0;
	while (i < 8)
	{
		buf[i + 0] = g_hex_arr[hsh.a >> g_tbl[i] & B];
		buf[i + 8] = g_hex_arr[hsh.b >> g_tbl[i] & B];
		buf[i + 16] = g_hex_arr[hsh.c >> g_tbl[i] & B];
		buf[i + 24] = g_hex_arr[hsh.d >> g_tbl[i] & B];
		i++;
	}
	buf[32] = 0;
	return (buf);
}

void		print_md5(t_hash_md5 hsh, char *str, int flags)
{
	char	*md5_hash_string;

	md5_hash_string = raw_md5(hsh);
	if (hsh.error == 1)
		nstrprinterror(3, "md5: ", str, ": Is a directory\n");
	else if (hsh.error == 2)
		nstrprinterror(3, "md5: ", str, ": No such file or directory\n");
	else if (flags & FLAG_P)
	{
		nstrprint(2, md5_hash_string, "\n");
	}
	else if (flags & FLAG_Q || flags & FLAG_STDIN)
		nstrprint(2, md5_hash_string, "\n");
	else if (flags & FLAG_R)
		nstrprint(5, md5_hash_string,
					(flags & FLAG_S) ? " \"" : " ",
					str,
					(flags & FLAG_S) ? "\"" : "", "\n");
	else
		nstrprint(6, "MD5",
					(flags & FLAG_S) ? " (\"" : " (",
					str,
					(flags & FLAG_S) ? "\") = " : ") = ",
					md5_hash_string, "\n");
	free(md5_hash_string);
}
