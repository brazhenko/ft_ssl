#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(int c, char **v)
{
	int fd;
	int rd;
	char byte;

	if (c == 2)
	{
		fd = open(v[1], O_RDONLY);
		if (fd < 0)
		{
			perror("Cannot open file: ");
			exit(1);
		}
		while ((rd = read(fd, &byte, 1)))
		{
			if (rd < 0)
			{
				perror("Cannot read: ");
				exit(1);
			}
			printf("%d ", byte);
		}
	}
	else if (c == 3 && strcmp(v[1], "x") == 0)
	{
		fd = open(v[2], O_RDONLY);
		if (fd < 0)
		{
			perror("Cannot open file: ");
			exit(1);
		}
		while ((rd = read(fd, &byte, 1)))
		{
			if (rd < 0)
			{
				perror("Cannot read: ");
				exit(1);
			}
			printf("%x ", byte);
		}
	}
	else puts("usage: ./mm [hex] [file]");

	fflush(stdout);
}
