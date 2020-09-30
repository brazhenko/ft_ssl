/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 03:17:13 by lreznak-          #+#    #+#             */
/*   Updated: 2020/09/24 10:09:21 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "base64.h"

size_t		encode_base64_block(unsigned char *buf,
							char *output_buf,
							ssize_t rd)
{
	ssize_t		i;

	i = 0;
	while (i < rd)
	{
		if (i % 3 == 0)
			output_buf[i + i / 3] = g_base64_arr[buf[i] >> 2u];
		else if (i % 3 == 1)
			output_buf[i + (i - 1) / 3] = g_base64_arr[
										((buf[i - 1] & 0b11u) << 4u) |
										(buf[i] >> 4u)];
		else if (i % 3 == 2)
		{
			output_buf[i + (i - 2) / 3] =
				g_base64_arr[((buf[i - 1] & 0b1111u) << 2u) | (buf[i] >> 6u)];
			output_buf[i + (i - 2) / 3 + 1] = g_base64_arr[buf[i] & 0b111111u];
		}
		i++;
	}
	return (i);
}

void		encode_base64_block_with_padding(
		uint8_t *buf,
		char *output_buf,
		ssize_t rd
)
{
	size_t		i;

	i = encode_base64_block(buf, output_buf, rd);
	if (i % 3 == 1)
	{
		output_buf[i + (i - 1) / 3] = g_base64_arr[
				((buf[i - 1] & 0b11u) << 4u)
				];
		output_buf[i + (i - 1) / 3 + 1] = '=';
		output_buf[i + (i - 1) / 3 + 2] = '=';
	}
	else if (i % 3 == 2)
	{
		output_buf[i + (i - 2) / 3] =
				g_base64_arr[((buf[i - 1] & 0b1111u) << 2u)];
		output_buf[i + (i - 2) / 3 + 1] = '=';
	}
}

void		base64_encode(t_encode_context *ctx)
{
	ssize_t			rd;
	uint8_t			buf[BASE64_ENCODE_READ_LEN];
	char			output_buf[BASE64_ENCODE_OUTPUT_LEN + 1];

	while ((rd = read(ctx->input_fd, buf, BASE64_ENCODE_READ_LEN)) > 0)
	{
		memset(output_buf, 0, sizeof(output_buf));
		if (rd < BASE64_ENCODE_READ_LEN)
		{
			encode_base64_block_with_padding(&buf[0], &output_buf[0], rd);
			write(ctx->output_fd, output_buf,
					(rd + (rd % 3 ? 3 - (rd % 3) : 0)) / 3 * 4);
		}
		else
		{
			encode_base64_block(&buf[0], &output_buf[0], rd);
			write(ctx->output_fd, output_buf, BASE64_ENCODE_OUTPUT_LEN);
		}
	}
	write(ctx->output_fd, "\n", 1);
}
