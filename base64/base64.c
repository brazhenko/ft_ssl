# define BASE64BUF_LEN 64
# include "ssl.h"

#include "ssl.h"
#include <stddef.h>

void		*base64(char *str, int flags)
{
	return (NULL);
}

// prints to the output
void 		*encode_fd_to_base64(int inp_fd)
{

	return (NULL);
}

void		*encode_str_to_base64(char *str)
{
	unsigned char		tmp;
	char				buf[BASE64BUF_LEN];
	size_t 				i;
	size_t				j;

	tmp = 0;
	i = 0;

	j = 0;
	while (str[i])
	{
		if (i % 3 == 0)
		{
			buf[j] = base64_arr[(str[i] >> 2)];
			j++;
			tmp |= ((str[i] & 0b11) << 4);
		}
		else if (i % 3 == 1)
		{
			tmp |= ((str[i] & 0b11) << 4);
		}
		else
		{

		}
		i++;
	}
	return (NULL);
}
