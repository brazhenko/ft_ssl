//
// Created by 17641238 on 09.07.2020.
//

#include "multiprecision.h"
#include <utilities.h>
#include <string.h>
#include <stdlib.h>

t_big_int		*mk_big_int(int init_value)
{
	t_big_int		*ret;
	long long		tmp;

	tmp = init_value;
	ret = xmalloc(sizeof(*ret));
	memset(ret, 0, sizeof(*ret));
	ret->array = xmalloc(sizeof(uint64_t) * INIT_CELLS_COUNT);
	memset(ret->array, 0, sizeof(uint64_t) * INIT_CELLS_COUNT);
	ret->cell_count = INIT_CELLS_COUNT;
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
