#include <stdlib.h>
#include "utilities.h"
#include "base64.h"

void		encode_option_requires_argument_exit(const char *opt)
{
	nstrprinterror(3, "option requires an argument -- ", opt, "\n");
	encode_usage();
	exit(EXIT_FAILURE);
}

void		encode_invalid_option_exit(const char *opt)
{
	nstrprinterror(3, "invalid option -- ", opt, "\n");
	encode_usage();
	exit(EXIT_FAILURE);
}
