#include "utilities.h"
#include <stdlib.h>

void		encode_usage(void)
{
	nstrprinterror(8, "Usage:  ft_ssl ",
			"[encoding_algorithm] " ,
			"[-hed] [-i in_file] [-o out_file]\n",
			"\t-h\tdisplay this message\n",
			"\t-e\tencodes input (default)\n",
			"\t-d\tdecodes input\n",
			"\t-i\tinput file (default stdin)\n",
			"\t-o\toutput file (default stdout)\n");
}

void		encode_print_usage_exit()
{
	encode_usage();
	exit(EXIT_SUCCESS);
}