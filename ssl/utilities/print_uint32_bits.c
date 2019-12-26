#include <unistd.h>
#include <string.h>

void print_uint32_bits(unsigned num)
{
	char 	arr[33];
	size_t	i;

	memset(arr, 0, sizeof(arr));
	arr[32] = '\n';
	i = 0;
	while (i < 32)
	{
		arr[i] = ((num >> (31 - i)) & 1) ? '1' : '0';
		i++;
	}
	write(STDOUT_FILENO, arr, sizeof(arr));
}