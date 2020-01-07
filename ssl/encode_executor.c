#include "base64.h"

void		encode_executor(int ac, char **av,
		void *(*algo)(t_encode_context*))
{
	t_encode_context	*ctx;
	ctx = parse_encode_argv(ac, av);
	algo(ctx);
	destruct_encode_context(ctx);
}
