/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_rsautl.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 19:11:50 by a17641238         #+#    #+#             */
/*   Updated: 2020/09/29 19:13:11 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_INTERNAL_RSAUTL_H
# define FT_SSL_INTERNAL_RSAUTL_H

union		u_encryptor
{
	uint64_t			numero;
	unsigned char		arr[8];
};

int			len_till_pad(const unsigned char *inp);

#endif
