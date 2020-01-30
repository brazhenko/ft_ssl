/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:30:59 by a17641238         #+#    #+#             */
/*   Updated: 2020/01/30 17:30:59 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utilities.h"
#include "base64.h"

void		encode_option_requires_argument_exit(const char *opt)
{
	nstrprinterror(3, "option requires an argument -- ", opt, "\n");
	encode_usage();
	exit(EXIT_FAILURE);
}

void		encode_invalid_option_exit(const char *opt)
{
	nstrprinterror(3, "invalid option -- ", opt, "\n");
	encode_usage();
	exit(EXIT_FAILURE);
}
