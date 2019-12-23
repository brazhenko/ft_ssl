# include "ssl.h"
# include "base64.h"
#include <stddef.h>

typedef enum	e_state
{
	modzero,
	modone,
	modetwo
}				t_state;

static size_t 	calc_base64_block(
									unsigned char *buf,
									char *output_buf,
									ssize_t rd,
									t_base64_context *ctx
									)
{
	size_t		i;
	t_state		st;

	i = 0;
	st = modzero;
	while (i < rd)
	{
		if (st == modzero)
		{
			// puts("modzero");
			output_buf[i + i/3] = base64_arr[buf[i] >> 2u];
			st = modone;
		}
		else if (st == modone)
		{
			// puts("modone");
			output_buf[i + (i-1)/3] = base64_arr[((buf[i-1] & 0b11u)<<4u)|(buf[i]>>4u)];
			st = modetwo;
		}
		else if (st == modetwo)
		{
			// puts("modtwo");
			output_buf[i + (i-2)/3] = base64_arr[ ((buf[i-1]&0b1111u)<<2u)|(buf[i]>>6u) ];
			output_buf[i + (i-2)/3 + 1] = base64_arr[buf[i]&0b111111u];
			st = modzero;
		}
		i++;
	}
	return (i);
}

static void			calc_base64_block_with_padding(
													unsigned char *buf,
													char *output_buf,
													ssize_t rd,
													t_base64_context *ctx
													)
{
	size_t		i;

	i = calc_base64_block(buf, output_buf, rd, ctx);
	if (i % 3 == 1)
	{
		// puts("end: modone");
		output_buf[i + (i-1)/3] = base64_arr[
				((buf[i-1]&0b11u)<<4u) ];
		output_buf[i + (i-1)/3 + 1] = '=';
		output_buf[i + (i-1)/3 + 2] = '=';
		// output_buf[i + (i-1)/3 + 3] = '\n';
	}
	else if (i % 3 == 2)
	{
		// puts("end: modtwo");
		output_buf[i + (i-2)/3] = base64_arr[ ((buf[i-1]&0b1111u)<<2u) ];
		output_buf[i + (i-2)/3 + 1] = '=';
		// output_buf[i + (i-2)/3 + 2] = '\n';
	}
}

void		*base64(t_base64_context *ctx)
{
	// puts("DEBUG: base64()");
	ssize_t			rd;
	unsigned char	buf[BASE64_READ_LEN];
	char 			output_buf[BASE64_OUTPUT_LEN];

	// printf("buffers' lens: %d -- %d\n", BASE64_READ_LEN, BASE64_OUTPUT_LEN);
	while ((rd = read(ctx->input_fd, buf, BASE64_READ_LEN)) > 0)
	{
		memset(output_buf, 0, sizeof(output_buf));
		if (rd < BASE64_READ_LEN)
		{
			calc_base64_block_with_padding(&buf[0], &output_buf[0], rd, ctx);
		}
		else
		{
			calc_base64_block(&buf[0], &output_buf[0], rd, ctx);
		}
		write(ctx->output_fd, output_buf, strlen(output_buf)); // TODO fix strlen
	}
	write(1, "\n", 1);
	return (NULL);
}

