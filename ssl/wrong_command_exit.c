#include "ssl.h"

void 	wrong_command_exit(char *av0, char *command)
{
	nstrprinterror(4,
			av0, ": Error: \'", command, "\' is an invalid command.\n");
	print_ft_ssl_help();
	exit(EXIT_FAILURE);
}