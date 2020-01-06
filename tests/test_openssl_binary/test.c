#include <stdio.h>
#include <unistd.h>

int	main()
{
	unsigned long int a = 0x2246E7E31F4DA875;
	
	write(1, &a, sizeof(a));
}
