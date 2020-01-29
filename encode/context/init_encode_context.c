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
