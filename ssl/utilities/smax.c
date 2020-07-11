//
// Created by 17641238 on 10.07.2020.
//

#include <stddef.h>

size_t	max1(size_t l, size_t r)
{
	if (l > r)
		return l;
	return r;
}

size_t	min1(size_t l, size_t r)
{
	if (l < r)
		return l;
	return r;
}