#include "des.h"

void		cipher_executor(int ac, char **av,
		void *(*algo)(t_cipher_context *))
{
	t_cipher_context		*ctx;

	ctx = init_cipher_context(algo);
	ctx = parse_des_argv(ctx, ac, av);
	algo(ctx);
	destruct_cipher_context(ctx);
}
