# include "ssl.h"
# include "base64.h"
#include <stddef.h>

typedef enum	e_state
{
	start,
	modzero,
	modone,
	modetwo
}				t_state;

void		*base64(t_base64_context *ctx)
{
	puts("DEBUG: base64()");
	ssize_t			rd;
	size_t			i;
	unsigned char	buf[BASE64_READ_LEN];
	char 			output_buf[BASE64_OUTPUT_LEN];
	t_state			st;

	st = start;
	printf("buffers' lens: %d -- %d\n", BASE64_READ_LEN, BASE64_OUTPUT_LEN);
	while ((rd = read(ctx->input_fd, buf, BASE64_READ_LEN)) > 0)
	{
		i = 0;
		memset(output_buf, 0, sizeof(output_buf));
		while (i < rd)
		{
			if (st == start)
			{
				puts("start");
				output_buf[i] = base64_arr[buf[i] >> 2];
				output_buf[i+1] = '@';
				output_buf[i+2] = '@';
				output_buf[i+3] = '@';
				st = modone;
			}
			else if (st == modzero)
			{
				puts("modzero");
				output_buf[i + i/3] = base64_arr[buf[i] >> 2];
				output_buf[i + i/3 + 1] = '@';
				output_buf[i + i/3 + 2] = '@';
				output_buf[i + i/3 + 3] = '@';
				st = modone;
			}
			else if (st == modone)
			{
				puts("modone");
				st = modetwo;
			}
			else if (st == modetwo)
			{
				puts("modetwo");

				st = modzero;
			}
			i++;
		}
		write(ctx->output_fd, output_buf, sizeof(output_buf));
	}
	return (NULL);
}

