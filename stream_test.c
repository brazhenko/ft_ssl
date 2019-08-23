#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	int fd = open(argv[1], O_RDONLY);
	char buf[16];

	printf("%d\n", fd);
	read(0, buf, 16);
	write(1, buf, 16);

}
