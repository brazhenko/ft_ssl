#ifndef FT_SSL_H
# define FT_SSL_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

# define FLAG_R 0b1
# define FLAG_Q 0b10
# define FLAG_S 0b100
# define FLAG_P 0b1000

int			command_executor(int ac, char *av[]);
void		*md5(const char *str, int *flags);

#endif
