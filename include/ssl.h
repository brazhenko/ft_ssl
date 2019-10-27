#ifndef FT_SSL_H
# define FT_SSL_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "sha256.h"
#include "utilities.h"

# define FLAG_R 		0b1
# define FLAG_Q 		0b10
# define FLAG_S 		0b100
# define FLAG_P 		0b1000
# define FLAG_STDIN 	0b10000
# define FLAG_FILEERROR 0b10000000
# define RESET_FLAG     0b1111111101110011

typedef uint32_t		reg32;
typedef unsigned char	byte;




void		*md5(char *str, int flags);
int			command_executor(int ac, char *av[]);

#endif
