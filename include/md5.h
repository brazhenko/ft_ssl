/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:02:47 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/28 23:02:53 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# include "ssl.h"

# define FUNC_F(x, y, z) (((x) & (y)) | ((~(x)) & (z)))
# define FUNC_G(x, y, z) (((x) & (z)) | (~(z) & (y)))
# define FUNC_H(x, y, z) ((x) ^ (y) ^ (z))
# define FUNC_I(x, y, z) ((y) ^ (~(z) | (x)))

# define LROT(x, n) ((x) << (n) | (x) >> (32 - (n)))

# define ROUND1(a,b,c,d,xk,s,i) a=b+LROT(a+FUNC_F(b,c,d)+xk+g_md5_vals[i-1],s);

# define ROUND2(a,b,c,d,xk,s,i)a=b+LROT(a+FUNC_G(b,c,d)+xk+g_md5_vals[i-1],s);

# define ROUND3(a,b,c,d,xk,s,i)a=b+LROT(a+FUNC_H(b,c,d)+xk+g_md5_vals[i-1],s);

# define ROUND4(a,b,c,d,xk,s,i)a=b+LROT(a+FUNC_I(b,c,d)+xk+g_md5_vals[i-1],s);

static const unsigned g_md5_vals[64] = {
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

typedef struct			s_hash_md5
{
	reg32	a;
	reg32	b;
	reg32	c;
	reg32	d;
	int		error;
}						t_hash_md5;

void					*md5(char *str, int flags);
int						init_md5_hash(t_hash_md5 *hash);
t_hash_md5				calculate_md5_from_string(const char *str);
t_hash_md5				calculate_md5_from_stdin(int flag_p);
t_hash_md5				calculate_md5_from_file(const char *file_name);
int						calculate_md5_block(reg32 *ptr, t_hash_md5 *hash);

#endif