#include <string.h>
#include <unistd.h>
#include <stdio.h>

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

int			print_bit_char(char num)
{
	for (int j = 7; j >= 0; --j)
	{
		write(1, ((num >> j) & 1 ? "1" : "0"), 1);
	}
	write(1, " ", 1);
	return (0);
}

void		print_bit_str(const char *comment, char *str, size_t len)
{
	printf("%s", comment);
	fflush(stdout);
	for (size_t i = 0;i < len; i++)
	{
		print_bit_char(str[i]);
	}
	write(1, "\n", 1);
}

int			print_bit_num(int num)
{
	for (int j = 31; j >= 0; --j)
	{
		write(1, ((num >> j) & 1 ? "1" : "0"), 1);
	}
	write(1, " ", 1);
	return (0);
}

void		print_bit_nums(int *str, size_t len)
{
	for (size_t i = 0;i < len; i++)
	{
		print_bit_num(str[i]);
	}
	write(1, "\n", 1);
}