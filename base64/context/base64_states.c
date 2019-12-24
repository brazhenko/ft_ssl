#include "base64.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

t_base64_context	*base64_state_d(int argc, char **argv, t_base64_context *ctx)
{
	set_base64_decode_mode(ctx);
	if (!(*argv))
		return (ctx);
	else if (strcmp(*argv, "-d") == 0)
		return (base64_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (base64_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (base64_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (base64_state_o(argc - 1, argv  + 1, ctx));
	else if (strcmp(*argv, "-h") == 0)
		encode_print_usage_exit();
	else
		encode_invalid_option_exit(*argv);
	return (ctx);
}

t_base64_context	*base64_state_e(int argc, char **argv, t_base64_context *ctx)
{
	set_base64_encode_mode(ctx);
	if (!(*argv))
		return (ctx);
	else if (strcmp(*argv, "-d") == 0)
		return (base64_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (base64_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (base64_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (base64_state_o(argc - 1, argv  + 1, ctx));
	else if (strcmp(*argv, "-h") == 0)
		encode_print_usage_exit();
	else
		encode_invalid_option_exit(*argv);
	return (ctx);
}

t_base64_context	*base64_state_i(int argc, char **argv, t_base64_context *ctx)
{
	if (!(*argv))
	{
		encode_option_requires_argument_exit("i");
	}
	else
		set_base64_input_file(ctx, *argv);
	argv++;
	argc--;
	if (!(*argv))
		return (ctx);
	else if (strcmp(*argv, "-d") == 0)
		return (base64_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (base64_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (base64_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (base64_state_o(argc - 1, argv  + 1, ctx));
	else if (strcmp(*argv, "-h") == 0)
		encode_print_usage_exit();
	else
		encode_invalid_option_exit(*argv);
	return (ctx);
}

t_base64_context	*base64_state_o(int argc, char **argv, t_base64_context *ctx)
{
	if (!(*argv))
	{
		encode_option_requires_argument_exit("o");
	}
	else
		set_base64_output_file(ctx, *argv);
	argv++;
	argc--;
	if (!(*argv))
		return (ctx);
	else if (strcmp(*argv, "-d") == 0)
		return (base64_state_d(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-e") == 0)
		return (base64_state_e(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-i") == 0)
		return (base64_state_i(argc - 1, argv + 1, ctx));
	else if (strcmp(*argv, "-o") == 0)
		return (base64_state_o(argc - 1, argv  + 1, ctx));
	else if (strcmp(*argv, "-h") == 0)
		encode_print_usage_exit();
	else
		encode_invalid_option_exit(*argv);
	return (ctx);
}