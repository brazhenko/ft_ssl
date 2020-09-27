//
// Created by 17641238 on 27.09.2020.
//

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <utilities.h>

void 		fatal(const char *s)
{
	nstrprinterror(2, s, "\n");
	exit(1);
}