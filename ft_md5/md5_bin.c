byte		*lgc_and(byte *left, byte *right)
{
	byte	*res;
	size_t	i;

	res = (byte *)malloc(WORD_LEN);
	i = 0;
	while (i < WORD_LEN)
	{
		res[i] = left[i] & right[i];
	}
	return (res);
}

byte		*lgc_or(byte *left, byte *right)
{
	byte	*res;
	size_t	i;

	res = (byte *)malloc(WORD_LEN);
	i = 0;
	while (i < WORD_LEN)
	{
		res[i] = left[i] | right[i];
	}
	return (res);
}

byte		*lgc_xor(byte *left, byte *right)
{
	byte	*res;
	size_t	i;

	res = (byte *)malloc(WORD_LEN);
	i = 0;
	while (i < WORD_LEN)
	{
		res[i] = left[i] ^ right[i];
	}
	return (res);
}
byte		*lgc_not(byte *word)
{
	byte	*res;
	size_t	i;

	res = (byte *)malloc(WORD_LEN);
	i = 0;
	while (i < WORD_LEN)
	{
		res[i] = ~word[i];
	}
	return (res);
}

byte		*fun_f(reg32 x, reg32 y, reg32 z)
{
	reg32	res;
	reg32	tmp;
	reg32	tmp2;
	reg32	tmp3;

//	tmp = lgc_and(x, y) x & y;
//	tmp2 = lgc_not(x) ~x;
//	tmp3 = lgc_and(tmp2, z);
//	res = lgc_or(tmp, tmp3);
//
//	free(tmp);
//   	free(tmp2);
//	free(tmp3);	
	return (res);
}

void		*fun_g(byte *x, byte *y, byte *z)
{
	byte	*res;
	byte	*tmp;
	byte	*tmp2;
	byte	*tmp3;

	tmp = lgc_not(x);
	tmp2 = lgc_and(tmp, z);
	tmp3 = lgc_and(x, y);
	res = lgc_or(tmp2, tmp3);

	free(tmp);
	free(tmp2);
	free(tmp3);
	return (res);
}

void		*fun_h(byte *x, byte *y, byte *z)
{
	byte	*res;
	byte	*tmp;

	tmp = lgc_xor(x, y);
	res = lgc_xor(tmp, z);

	free(tmp);
	return (res);
}

void		*fun_i(byte *x, byte *y, byte *z)
{
	byte		*res;
	byte		*tmp;
	byte		*tmp2;

	tmp = lgc_not(z);
	tmp2 = lgc_or(tmp, x);
	res = lgc_xor(y, tmp2);
	
	free(tmp);
	free(tmp2);
	return (res);
}
