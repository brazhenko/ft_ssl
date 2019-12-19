#include "base64.h"
#include <string.h>
#include "utilities.h"

t_base64_context 	*init_base64_context(void)
{
	t_base64_context		*ret;

	ret = (t_base64_context *)xmalloc(sizeof(t_base64_context));
	ret = memset(ret, '\0', sizeof(t_base64_context));
	ret->input_fd = 0;
	ret->output_fd = 1;
	return (ret);
}