#include "ssl.h"
#include "base64.h"
#include "des.h"

void		encode_executor(int ac, char **av,
		void *(*algo)(t_encode_context*))
{
	t_encode_context	*ctx;
	ctx = parse_encode_argv(ac, av);
	algo(ctx);
	destruct_encode_context(ctx);
}

void		cipher_executor(int ac, char **av, void *(*algo)(t_cipher_context *))
{
	t_cipher_context		*ctx;
	ctx = parse_des_argv(ac, av);
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