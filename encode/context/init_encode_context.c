/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_encode_context.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:31:05 by a17641238         #+#    #+#             */
/*   Updated: 2020/01/30 17:31:05 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"
#include <string.h>
#include "utilities.h"

t_encode_context	*init_encode_context(void)
{
	t_encode_context		*ret;

	ret = (t_encode_context *)xmalloc(sizeof(t_encode_context));
	ret = memset(ret, '\0', sizeof(t_encode_context));
	ret->input_fd = 0;
	ret->output_fd = 1;
	return (ret);
}
