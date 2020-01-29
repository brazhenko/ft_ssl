#include <unistd.h>
#include <string.h>

void		print_uint64_bits(uint64_t num)
{
	char		arr[65];
	size_t		i;

	memset(arr, 0, sizeof(arr));
	arr[64] = '\n';
	i = 0;
	while (i < 64)
	{
		arr[i] = ((num >> (63 - i)) & 1) ? '1' : '0';
		i++;
	}
	write(STDOUT_FILENO, arr, sizeof(arr));
}
