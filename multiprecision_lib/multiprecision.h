

#ifndef FT_SSL_MULTIPRECISION_H
# define FT_SSL_MULTIPRECISION_H

# include <stdint.h>
# include <stddef.h>
#include <stdbool.h>

# define VALUABLE_BITS_PER_CELL		62UL
# define INIT_CELLS_COUNT			35U
# define TAKE_BASE(X) ((X)&((1UL<<VALUABLE_BITS_PER_CELL)-1UL))
# define LITTLE_ENDIAN

typedef struct	s_big_int
{
	uint64_t	*array;
	size_t		cell_count;
	int			used_cell_count;
	bool		negative;
}				t_big_int;


t_big_int		*mk_big_int(int init_value);
t_big_int		*mk_big_int_cell_count_init(int init_value, size_t cell_count);
void			del_big_int(t_big_int *bi);
t_big_int		*big_int_dup(t_big_int *bi);
int 			big_int_cmp(t_big_int *le, t_big_int *ri);

t_big_int		*asci_to_big_int(const char *str);
char			*big_int_to_ascii(t_big_int *bi);




#endif
