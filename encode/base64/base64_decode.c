/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 05:57:01 by lreznak-          #+#    #+#             */
/*   Updated: 2020/02/03 13:52:18 by a17641238        ###   ########.fr       */
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

static bool			isbase64alpha(char c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z') ||
			('0' <= c && c <= '9') ||
			(c == '/') ||
			(c == '+') ||
			(c == '='));
}

void				dec(uint8_t *buf, char *out, char *tmp, size_t *arr)
{
	if ((arr[2] - arr[0]) % 4 == 0)
		tmp[0] = g_base64_dec_arr[buf[arr[2]]];
	else if ((arr[2] - arr[0]) % 4 == 1)
		tmp[1] = g_base64_dec_arr[buf[arr[2]]];
	else if ((arr[2] - arr[0]) % 4 == 2)
		tmp[2] = g_base64_dec_arr[buf[arr[2]]];
	else if ((arr[2] - arr[0]) % 4 == 3)
	{
		tmp[3] = g_base64_dec_arr[buf[arr[2]]];
		out[arr[1] * 3] = ((tmp[0] & 0b111111u) << 2u) +
				((tmp[1] >> 4u) & 0b11u);
		out[arr[1] * 3 + 1] = ((tmp[1] & 0b1111u) << 4u) +
				((tmp[2] >> 2u) & 0b1111u);
		out[arr[1] * 3 + 2] = ((tmp[2] & 0b11) << 6u) +
				((tmp[3] >> 0u) & 0b111111);
		arr[1]++;
	}
}

/*
** arr[3]: arr[0] - white_space offset, arr[1] - temporary num, arr[2] - i
*/

static void			base64_decode_block(
		uint8_t *buf,
		char *out,
		ssize_t rd,
		t_encode_context *ctx
)
{
	char		tmp[4];
	size_t		arr[3];

	arr[2] = 0;
	arr[1] = 0;
	arr[0] = 0;
	while (arr[2] < rd)
	{
		if (isbase64alpha(buf[arr[2]]))
			dec(buf, out, tmp, arr);
		else if (isspace(buf[arr[2]]))
			arr[0]++;
		else
		{
			nstrprinterror(1, "Invalid character in input stream.\n");
			exit(EXIT_FAILURE);
		}
		arr[2]++;
	}
}

void				base64_decode(t_encode_context *ctx)
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
