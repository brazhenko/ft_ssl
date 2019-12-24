#include "base64.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

t_base64_context	*parse_base64_argv(int argc, char **argv)
{
	t_base64_context	*ctx;

	ctx = init_base64_context();
	if (!(*argv))
		return (ctx);
	else if (strcmp(*argv, "-d") == 0)
	{
		return (base64_state_d(argc - 1, argv + 1, ctx));
	}
	else if (strcmp(*argv, "-e") == 0)
	{
		return (base64_state_e(argc - 1, argv + 1, ctx));
	}
	else if (strcmp(*argv, "-i") == 0)
	{
		return (base64_state_i(argc - 1, argv + 1, ctx));
	}
	else if (strcmp(*argv, "-o") == 0)
	{
		return (base64_state_o(argc - 1, argv  + 1, ctx));
	}
	else if (strcmp(*argv, "-h") == 0)
		encode_print_usage_exit();
	else
	{
		encode_invalid_option_exit(*argv);
	}
	return (ctx);
}