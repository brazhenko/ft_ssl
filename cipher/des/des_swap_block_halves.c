/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_swap_block_halves.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:34:39 by a17641238         #+#    #+#             */
/*   Updated: 2020/01/30 17:34:39 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include <string.h>

/*
 * des_swap_block_halves() gets des block pointer and swaps its 32bit halves
 */

void		des_swap_block_halves(t_lpdesblock bl)
{
	t_deshalfblock		tmp;

	memcpy(tmp, ((uint8_t*)(bl) + 4), 4);
	memcpy(((uint8_t*)bl + 4), bl, 4);
	memcpy(bl, tmp, 4);
}
