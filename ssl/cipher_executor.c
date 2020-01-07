#include "ssl.h"
#include "base64.h"
#include "des.h"

void		cipher_executor(int ac, char **av, void *(*algo)(t_cipher_context *))
{
	t_cipher_context		*ctx;

	ctx = init_des_context(algo);
	ctx = parse_des_argv(ctx, ac, av);
//	puts("____CIPHER_CTX____");
//	puts("ctx mode:");
//	print_uint32_bits(ctx->mode);
//	puts("salt:");
//	puts(ctx->salt);
//	puts("vector:");
//	puts(ctx->vector);
//	puts("pass:");
//	puts(ctx->password);
//	puts("out file:");
//	puts(ctx->output_file);
//	puts("in file:");
//	puts(ctx->input_file);
//	printf("inputfd:\n%d\n", ctx->input_fd);
//	printf("outputfd:\n%d\n", ctx->output_fd);
	algo(ctx);
}