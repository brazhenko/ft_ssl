#include <string.h>
#include <unistd.h>

int			print_bits(int num)
{
	{
		for (int j = 31; j >= 0; --j)
		{
			write(1, ((num >> j) & 1 ? "1" : "0"), 1);
			if (!(j % 8))
				write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
	return (0);
}

int			print_bits_char(char num)
{
	{
		for (int j = 7; j >= 0; --j)
		{
			write(1, ((num >> j) & 1 ? "1" : "0"), 1);
		}
		write(1, " ", 1);
	}
	return (0);
}

void		print_bit_str(char *str, size_t len)
{
	for (size_t i = 0;i < len; i++)
	{
		print_bits_char(str[i]);
	}
	write(1, "\n", 1);
}