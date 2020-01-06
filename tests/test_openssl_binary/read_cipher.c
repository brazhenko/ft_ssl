#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int	main(int ac, char **av)
{
	char	buf[8];
	int fd = open(av[1], O_RDONLY);

	memset(buf, 0, 8);
	while (read(fd, buf, 8)>0)
	{
		for (int i = 0; i < 8; i++)
		{
			printf("%d ", (char)buf[i]);
		}
		printf("\n");
		memset(buf, 0, 8);
	}
	printf("%s\n", av[1]);
}
