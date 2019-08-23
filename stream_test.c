#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argvp[])
{
	// int fd = open("main.c", O_RDONLY);
	char buf[16];

	read(0, buf, 16);
	write(1, buf, 16);

}
