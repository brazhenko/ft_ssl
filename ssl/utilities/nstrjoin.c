/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nstrjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:27:48 by lreznak-          #+#    #+#             */
/*   Updated: 2019/10/28 23:27:50 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*
**	(const) char * args are binded in one string
*/

char		*nstrjoin(int n, ...)
{
	va_list		argptr;
	int			n_cpy;
	size_t		len;
	char		*ptr;
	char		*str;

	n_cpy = n;
	len = 0;
	va_start(argptr, n);
	while (n--)
	{
		ptr = va_arg(argptr, char *);
		len += strlen(ptr);
	}
	va_end(argptr);
	str = (char *)malloc(len + 1);
	bzero(str, len + 1);
	va_start(argptr, n);
	while (n_cpy--)
	{
		ptr = va_arg(argptr, char *);
		str = strcat(str, ptr);
	}
	va_end(argptr);
	return (str);
}

static char	*strnew(size_t len)
{
	char	*ret;

	ret = (char *)malloc(len + 1);
	bzero(ret, len + 1);
	return (ret);
}

int			nstrprint(int n, ...)
{
	va_list		argptr;
	int			n_cpy;
	size_t		len;
	char		*ptr;
	char		*str;

	n_cpy = n;
	len = 0;
	va_start(argptr, n);
	while (n--)
	{
		len += strlen(va_arg(argptr, char *));
	}
	va_end(argptr);
	str = strnew(len);
	va_start(argptr, n);
	while (n_cpy--)
	{
		ptr = va_arg(argptr, char *);
		str = strcat(str, ptr);
	}
	va_end(argptr);
	write(1, str, len);
	free(str);
	return (len);
}

int			nstrprinterror(int n, ...)
{
	va_list		argptr;
	int			n_cpy;
	size_t		len;
	char		*ptr;
	char		*str;

	n_cpy = n;
	len = 0;
	va_start(argptr, n);
	while (n--)
	{
		len += strlen(va_arg(argptr, char *));
	}
	va_end(argptr);
	str = strnew(len);
	va_start(argptr, n);
	while (n_cpy--)
	{
		ptr = va_arg(argptr, char *);
		str = strcat(str, ptr);
	}
	va_end(argptr);
	write(2, str, len);
	free(str);
	return (len);
}
