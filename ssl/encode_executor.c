#include "ssl.h"
#include "base64.h"

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