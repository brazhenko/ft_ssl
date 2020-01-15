#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const uint8_t	hex2bin[] =
{
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u,
	8, 9, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 10u, 11u, 12u, 13u, 14u, 15u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 10u, 11u, 12u, 13u, 14u, 15u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
	0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
};

int	main(int c, char **v)
{
	int fd;
	int rd;
	char byte[2];

	if (c == 1)
	{
		fd = 0;//open(v[1], O_RDONLY);
		if (fd < 0)
		{
			perror("Cannot open file: ");
			exit(1);
		}
		while ((rd = read(fd, &byte, 2)))
		{
			if (rd < 0)
			{
				perror("Cannot read: ");
				exit(1);
			}
			else
			{
				printf("%c", (hex2bin[byte[0]] << 4) + (hex2bin[byte[1]]));
			}
		}
	}

	else puts("usage: ./hb ");

	fflush(stdout);
}
