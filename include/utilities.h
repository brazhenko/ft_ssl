/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:03:21 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/28 23:03:23 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# define MAX(x, y) ((x) > (y) ? (x) : (y))

static const char		hex_arr[] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'a', 'b',
	'c', 'd', 'e', 'f'
};

char	*nstrjoin(int n, ...);
int		nstrprint(int n, ...);
int		nstrprinterror(int n, ...);
int		is_flag(const char *str);

#endif
