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