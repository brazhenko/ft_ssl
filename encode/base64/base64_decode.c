#include <ntsid.h>
#include "base64.h"
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum e_decode_states
{
	modzero,
	modone,
	modtwo,
	modthree,
	end
}				some_enum;

static bool		isbase64alpha(char c)
{
	return (
			('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z') ||
			('0' <= c && c <= '9') ||
			(c == '/') ||
			(c == '+') ||
			(c == '=')
			);
}



static void		base64_decode_block(
		uint8_t *buf,
		char *output_buf,
		ssize_t rd,
		t_encode_context *ctx
		)
{
	static enum	e_decode_states st = modzero;
	char 		tmp[4];
	size_t		i;
	size_t		tmp_num;

	i = 0;
	tmp_num = 0;
	while (i < rd)
	{
		if (isbase64alpha(buf[i]))
		{
			// change state to next;
			if (st == modzero)
			{
				tmp[0] = base64_dec_arr[buf[i]];
				st = modone;
			}
			else if (st == modone)
			{
				tmp[1] = base64_dec_arr[buf[i]];
				st = modtwo;
			}
			else if (st == modtwo)
			{
				tmp[2] = base64_dec_arr[buf[i]];
				st = modthree;
			}
			else if (st == modthree)
			{
				tmp[3] = base64_dec_arr[buf[i]];
				output_buf[tmp_num * 3] = ((tmp[0] & 0b111111u)<<2u) + ((tmp[1]>>4u)&0b11u);
				output_buf[tmp_num * 3 + 1] = ((tmp[1]&0b1111u)<<4u) + ((tmp[2]>>2u)&0b1111u);
				output_buf[tmp_num * 3 + 2] = ((tmp[2]&0b11)<<6u) + ((tmp[3]>>0u)&0b111111);
				tmp_num++;
				st = modzero;
			}
			//----------------------
		}
		else if (isspace(buf[i]))
		{
			// pass
		}
		else if (buf[i] == '=')
		{
			// ???
		}
		else
		{
			puts("base64_decode_block(): undefined symbol");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void 			base64_decode(t_encode_context *ctx)
{
	ssize_t			rd;
	size_t			i;
	uint8_t			input_buf[BASE64_DECODE_READ_LEN];
	char 			output_buf[BASE64_DECODE_OUTPUT_LEN];

	while ((rd = read(ctx->input_fd, input_buf, BASE64_DECODE_READ_LEN)) > 0)
	{
		memset(output_buf, 0, sizeof(output_buf));
		i = 0;
		base64_decode_block(&input_buf[0], &output_buf[0], rd, ctx);
		write(ctx->output_fd, output_buf, strlen(output_buf)); // TODO fix hardcode
	}
}