#ifndef UTILITIES_H
# define UTILITIES_H

static const char 		hex_arr[] = {
		'0', '1', '2', '3',
		'4', '5', '6', '7',
		'8', '9', 'a', 'b',
		'c', 'd', 'e', 'f'
};

char	*nstrjoin(int n, ...);
int		nstrprint(int n, ...);
int		is_flag(const char *str);

#endif
