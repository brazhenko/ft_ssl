#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

# define READ_SZ 5120

int	main(int ac, char *av[], char *en[])
{
	int fd;
	char buffer[READ_SZ];
	size_t read_count = 0;
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		struct stat file;
		int ret = stat(av[1], &file);
		printf("ret: %d\nfile size: %llu\nblocks per file: %llu\n", ret, file.st_size, file.st_blocks);
		int rd = 0;
		while ((rd = read(fd, buffer, READ_SZ)))
		{
			//pass
			read_count++;
		}
		printf("read_count: %lu\n", read_count);
	}

	close(fd);
	return 0;
}