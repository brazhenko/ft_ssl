#include "base64.h"
#include <stdlib.h>
#include "utilities.h"
#include <string.h>

t_base64_context 	*init_base64_context(void)
{
	t_base64_context		*ret;

	ret = (t_base64_context *)xmalloc(sizeof(t_base64_context));
	ret = memset(ret, '\0', sizeof(t_base64_context));
	return (ret);
}