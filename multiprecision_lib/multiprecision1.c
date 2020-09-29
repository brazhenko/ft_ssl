//
// Created by 17641238 on 09.07.2020.
//

#include "multiprecision.h"
#include <utilities.h>
#include <string.h>
#include <stdlib.h>

t_big_int		*mk_big_int(int init_value)
{
	return (mk_big_int_cell_count_init(init_value, INIT_CELLS_COUNT));
}

t_big_int		*mk_big_int_cell_count_init(int init_value, size_t cell_count)
{
	t_big_int		*ret;
	long long		tmp;

	tmp = init_value;
	ret = xmalloc(sizeof(*ret));
	memset(ret, 0, sizeof(*ret));
	ret->array = xmalloc(sizeof(uint64_t) * cell_count);
	memset(ret->array, 0, sizeof(uint64_t) * cell_count);
	ret->cell_count = cell_count;
	if (tmp < 0)
	{
		tmp = -tmp;
		ret->negative = true;
	}
	ret->array[0] = tmp;
	ret->used_cell_count = 1;
	return (ret);
}

void			del_big_int(t_big_int *bi)
{
	free(bi->array);
	memset(bi, 0, sizeof(*bi));
	free(bi);
}

t_big_int		*big_int_dup(t_big_int *bi)
{
	t_big_int	*ret;

	ret = xmalloc(sizeof(*ret));
	memset(ret, 0, sizeof(*ret));
	ret->array = xmalloc(sizeof(uint64_t) * bi->cell_count);
	memcpy(ret->array, bi->array, sizeof(uint64_t) * bi->cell_count);
	ret->cell_count = bi->cell_count;
	ret->used_cell_count = bi->used_cell_count;
	ret->negative = bi->negative;
	return ret;
}

int 			big_int_cmp(t_big_int *le, t_big_int *ri)
{
	int i;

	if (le->used_cell_count != ri->used_cell_count)
		return (le->used_cell_count - ri->used_cell_count);
	i = le->used_cell_count - 1;
	while (i > -1)
	{
		if (TAKE_BASE(le->array[i]) != TAKE_BASE(ri->array[i]))
		{
			if (TAKE_BASE(le->array[i]) < TAKE_BASE(ri->array[i]))
				return (-1);
			else
				return (1);
		}
		i--;
	}
	return (0);
}

t_big_int		*big_int_add(const t_big_int *le, const t_big_int *ri)
{
	const size_t	max_digit = max1(le->used_cell_count, ri->used_cell_count);
	const size_t	min_digit = min1(le->used_cell_count, ri->used_cell_count);
	t_big_int		*ret;
	size_t			i;
	uint64_t		rest;

	ret = mk_big_int_cell_count_init(0,
			1 + max_digit);
	i = 0;
	rest = 0;
	while (i < min_digit)
	{
		ret->array[i] = le->array[i] + le->array[i] + rest;
		rest = ret->array[i++] >> VALUABLE_BITS_PER_CELL;
	}
	if (le->used_cell_count < ri->used_cell_count)
		le = ri;
	while (i < max_digit)
	{
		ret->array[i] = le->array[i] + rest;
		rest = ret->array[i++] >>VALUABLE_BITS_PER_CELL;
	}
	if (rest)
		ret->array[i] = rest;
	return ret;
}