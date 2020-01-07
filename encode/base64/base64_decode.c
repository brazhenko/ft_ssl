/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 05:57:01 by lreznak-          #+#    #+#             */
/*   Updated: 2020/01/07 05:57:02 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <utilities.h>

static bool		isbase64alpha(char c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z') ||
			('0' <= c && c <= '9') ||
			(c == '/') ||
			(c == '+') ||
			(c == '='));
}

static void		base64_decode_block(
		uint8_t *buf,
		char *output_buf,
		ssize_t rd,
		t_encode_context *ctx
)
{
	char		tmp[4];
	size_t		i;
	size_t		tmp_num;
	size_t		wsoffset;

	i = 0;
	tmp_num = 0;
	wsoffset = 0;
	while (i < rd)
	{
		if (isbase64alpha(buf[i]))
		{
			if ((i - wsoffset) % 4 == 0)
				tmp[0] = base64_dec_arr[buf[i]];
			else if ((i - wsoffset) % 4 == 1)
				tmp[1] = base64_dec_arr[buf[i]];
			else if ((i - wsoffset) % 4 == 2)
				tmp[2] = base64_dec_arr[buf[i]];
			else if ((i - wsoffset) % 4 == 3)
			{
				tmp[3] = base64_dec_arr[buf[i]];
				output_buf[tmp_num * 3] =
						((tmp[0] & 0b111111u) << 2u) + ((tmp[1] >> 4u) & 0b11u);
				output_buf[tmp_num * 3 + 1] =
						((tmp[1] & 0b1111u) << 4u) + ((tmp[2] >> 2u) & 0b1111u);
				output_buf[tmp_num * 3 + 2] =
						((tmp[2] & 0b11) << 6u) + ((tmp[3] >> 0u) & 0b111111);
				tmp_num++;
			}
		}
		else if (isspace(buf[i]))
			wsoffset++;
		else
		{
			nstrprinterror(1, "Invalid character in input stream.\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void			base64_decode(t_encode_context *ctx)
{
	ssize_t			rd;
	uint8_t			input_buf[BASE64_DECODE_READ_LEN];
	char			output_buf[BASE64_DECODE_OUTPUT_LEN];

	while (memset(input_buf, 0, sizeof(input_buf)) &&
		(rd = read(ctx->input_fd, input_buf, BASE64_DECODE_READ_LEN)) > 0)
	{
		memset(output_buf, 0, sizeof(output_buf));
		base64_decode_block(&input_buf[0], &output_buf[0], rd, ctx);
		write(ctx->output_fd, output_buf, strlen(output_buf));
	}
}
