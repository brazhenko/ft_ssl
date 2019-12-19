#include "ssl.h"
#include "base64.h"
#include "des.h"

// TODO fix algo signature

void		encode_executor(int ac, char **av, void *(*algo)(char*, int))
{
	t_base64_context	*res;
	res = parse_base64_argv(ac, av);
	puts("____CTX_____");
	puts(res->output_file);
	puts(res->input_file);
	// TODO binary print, handle "else" (not waited argv's) in base64_states.c
	printf("%u\n", res->mode);
}

void		cipher_executor(int ac, char **av, void *(*algo)(char*, int))
{
	t_des_context		*res;
	res = parse_des_argv(ac, av);
	puts("____CIPHER_CTX____");
	puts("ctx mode:");
	print_uint32_bits(res->mode);
	puts("salt:");
	puts(res->salt);
	puts("vector:");
	puts(res->vector);
	puts("pass:");
	puts(res->password);
	puts("out file:");
	puts(res->output_file);
	puts("in file:");
	puts(res->input_file);
	printf("inputfd:\n%d\n", res->input_fd);
	printf("outputfd:\n%d\n", res->output_fd);
}